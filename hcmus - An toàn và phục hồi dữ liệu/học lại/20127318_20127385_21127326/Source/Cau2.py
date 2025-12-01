#!usr/bin/env python3
import base64
import hashlib
import re
import os
import os.path
from Crypto import Random
from Crypto import Cipher
from Crypto.Cipher import AES
import base64

# Define AESCipher object to decrypt encrypt password


class AESCipher(object):

    def __init__(self, key):
        self.bs = AES.block_size
        self.key = hashlib.sha256(key.encode()).digest()

    def encrypt(self, raw):
        raw = self._pad(raw)
        iv = Random.new().read(AES.block_size)
        cipher = AES.new(self.key, AES.MODE_CBC, iv)
        return base64.b64encode(iv + cipher.encrypt(raw.encode("latin-1")))

    def decrypt(self, enc):
        enc = base64.b64decode(enc)
        iv = enc[:AES.block_size]
        cipher = AES.new(self.key, AES.MODE_CBC, iv)
        pad = 16-(len(enc) % 16)
        if pad == 16:
            return self._unpad(cipher.decrypt(enc[AES.block_size:])).decode("latin-1")
        enc += bytes([pad])*pad
        return self._unpad(cipher.decrypt(enc[AES.block_size:])).decode("latin-1")[:-pad]

    def _pad(self, s):
        return s + (self.bs - len(s) % self.bs) * chr(self.bs - len(s) % self.bs)

    @staticmethod
    def _unpad(s):
        return s[:-ord(s[len(s)-1:])]


SECRET_SIGN = 'myFSSecretSign'


class MyFS:
    def __init__(self, filename, file_password='', mode='create'):
        # Create file system
        if mode == 'create':
            aes = AESCipher(file_password)
            self.sign = aes.encrypt(SECRET_SIGN)
            empty_data = [b'\00'] * 1024 * 1024 * 10  # 10MB
            f = open(filename, 'a+')
            f.write(self.sign.decode("utf-8"))
            f.write(''.join([x.decode("utf-8") for x in empty_data]))
            f.close()
        else:
            f = open(filename, 'rb')
            data = f.read(44)
            f.close()
            self.sign = data.decode("utf-8")

        # define data to save info of file
        self.filename = filename  # 44byte
        self.sector_list_file = 402 #this sector save list of file in file system
        self.sector_data = 914 #this sector save data of file
        self.lock = True #password or not

        # self.auth()

    # authenticate password user input
    def auth(self):
        key = input('[> Input the password: ')
        with open(self.filename, 'rb') as f:  # Đảm bảo mở đúng tệp volume
            cipher = f.read(44)  # Đọc phần mã hóa
            aes = AESCipher(key)
            try:
                plain = aes.decrypt(cipher)  # Giải mã cipher
                self.lock = (plain == SECRET_SIGN)
                if self.lock:
                    print('[> Unlock successfully ')
                else:
                    print('[> Wrong password')
            except Exception as e:
                print('[> Error while decrypting:', e)
                self.lock = False
        return self.lock

    # Set password
    def SetKey(self):
        print('[> Re-confirm your password !')
        if self.auth() == False:
            os.system('pause')
            return
        key = input('[> New passwod: ')
        newKey = AESCipher(key).encrypt(SECRET_SIGN)
        try:
            self.WriteBlock(1, newKey)
            print('Set new password successfully ^^')
        except:
            print('Error')

    # Read Block by position
    def ReadBlock(self, pos):
        file = open(self.filename, 'rb')
        file.seek((pos-1)*512)
        data = file.read(512)
        file.close()
        return data

    # Write to block by position
    def WriteBlock(self, pos, data):
        file = open(self.filename, 'r+b')
        file.seek((pos-1)*512)
        file.write(data)
        file.close()
    #find empty sector in list File sector
    def EmptySectorListFile(self):
        d = list(self.ReadBlock(2))
        for j in range(0, len(d)):
            if(d[j] == 0):
                return j + self.sector_list_file
        return -1

   #find empty sector in data sector
    def EmptySectorData(self):
        for i in range(3, 402):
            d = list(self.ReadBlock(i))
            for j in range(len(d)):
                if(d[j] == 0):
                    return (i-3)*512 + j + self.sector_data
        return -1

    #Sign sector to write data
    def SignedSector(self, pos):
        mS = int((pos-401)/512) + 2
        mB = pos - (mS-2)*512 - 401
        d = list(self.ReadBlock(mS))
        d[mB-1] = 65
        self.WriteBlock(mS, bytes(d))

    #import a file with filename
    def AppendFile(self, file_name, key=''):
        f = open(file_name, 'rb')
        data = f.read()
        f.close()
        sign = []
        if(key == ''):
            sign = [bytes(0) for _ in range(len(self.sign))]
        else:
            aes = AESCipher(key)
            sign = aes.encrypt(SECRET_SIGN)
            data = aes.encrypt(data.decode("latin-1"))
        filename, file_extension = os.path.splitext(file_name)
        header_data = b''
        for i in range(19):
            header_data += filename[i].encode(
                'ascii') if i < len(filename) else b'\00'
        for i in range(5):
            header_data += file_extension[i].encode(
                'ascii') if i < len(file_extension) else b'\00'
        file_size = len(data) + 4
        file_sector_data = self.EmptySectorData()
        header_data += file_size.to_bytes(4, byteorder='big') + \
            file_sector_data.to_bytes(4, byteorder='big')
        posSector = self.EmptySectorListFile()
        posOffset = 0
        isChange = False
        if posSector - 402 != 0:
            d = list(self.ReadBlock(posSector-1))
            for i in range(16):
                if(d[i*32] == 0):
                    posOffset = i
                    posSector -= 1
                    isChange = True
                    break

        d = list(self.ReadBlock(posSector))
        j = 0
        h = list(header_data)
        for i in range(posOffset*32, (posOffset+1)*32):
            d[i] = h[j]
            j += 1
        self.WriteBlock(posSector, bytes(d))
        if isChange == False:
            self.SignedSector(posSector)

        result = bytes(sign) + data
        posSectorData = self.EmptySectorData()
        self.WriteBlock(posSectorData, result)
        n = int(len(result)/512) + (len(result) % 512 != 0)
        for i in range(n):
            self.SignedSector(posSectorData+i)

    #list file in FileSystem
    def ListFiles(self):
        id = 0
        print(f'List file in {self.filename}')
        for pos in range(self.sector_list_file, self.sector_list_file+100):
            data = self.ReadBlock(pos)
            isEnd = False
            for i in range(16):
                signed = list(data)[id*32]
                if signed == 255:
                    id += 1
                    continue
                if signed == 0:
                    isEnd = True
                    break
                filename = data[(id)*32:(id)*32+19].decode("utf-8")
                file_ext = data[(id)*32+19:(id)*32+24].decode("utf-8")
                filename = ''.join([x for x in filename if x != '\x00'])
                file_ext = ''.join([x for x in file_ext if x != '\x00'])
                print(f'{id}. {filename}{file_ext}')
                id += 1
            if isEnd:
                break
                
    #Read a file by fileId
    def ReadAfile(self, id_file):
        mS = int(id_file/16) + self.sector_list_file
        data = self.ReadBlock(mS)

        id_file -= 16*(int(id_file/16))
        signed = list(data)[32*(id_file)]
        if signed == 0 or signed == 255:
            print('ID not found')
            return
        sector_data = data[(id_file+1)*32-4: (id_file+1)*32]
        file_size = data[(id_file+1)*32-8: (id_file+1)*32-4]
        filename = data[(id_file)*32:(id_file)*32+19].decode("utf-8")
        file_ext = data[(id_file)*32+19:(id_file)*32+24].decode("utf-8")
        pos = int.from_bytes(sector_data, byteorder='big', signed=True)
        file_size = int.from_bytes(file_size, byteorder='big', signed=True)

        data = self.ReadBlock(pos)
        cipher = data[:44]
        auth = False
        aes = ''

        print('[> Type "q" to exit')
        key = input('[> Input the password: ')
        if key == 'q':
            return
        try:
            aes = AESCipher(key)
            plain = aes.decrypt(cipher)
            if (plain == SECRET_SIGN):
                auth = True
                print('[> Unlock successfully ')
            else:
                print('[> Wrong password')
                os.system('pause')
        except:
            print('[> Wrong password')
            os.system('pause')

        if auth == False:
            return
        nS = int(file_size/512) + (file_size % 512 != 0)
        content = data[44:]
        for i in range(nS):
            content += self.ReadBlock(pos+i+1)
        data = aes.decrypt(content)
        choice = input('[> Do you want to export file to ./Output ? (Y/N): ')
        if choice == 'Y':
            filename = ''.join([x for x in filename if x != '\x00'])
            file_ext = ''.join([x for x in file_ext if x != '\x00'])
            path = './Output'
            if not os.path.exists(path):
                os.makedirs(path)
            f = open(os.path.join(path, f'{filename}{file_ext}'), 'w+b')
            f.write(bytes(data.encode("latin-1")))
            f.close()

    #set passwort for file
    def SetKeyFile(self, id_file):
        mS = int(id_file/16) + self.sector_list_file
        data = self.ReadBlock(mS)

        id_file -= 16*(int(id_file/16))
        signed = list(data)[32*(id_file)]
        if signed == 0 or signed == 255:
            print('ID not found')
            return

        sector_data = data[(id_file+1)*32-4: (id_file+1)*32]
        file_size = data[(id_file+1)*32-8: (id_file+1)*32-4]

        filename = data[(id_file)*32:(id_file)*32+19].decode("utf-8")
        file_ext = data[(id_file)*32+19:(id_file)*32+24].decode("utf-8")
        filename = ''.join([x for x in filename if x != '\x00'])
        file_ext = ''.join([x for x in file_ext if x != '\x00'])

        pos = int.from_bytes(sector_data, byteorder='big', signed=True)
        file_size = int.from_bytes(file_size, byteorder='big', signed=True)
        data = self.ReadBlock(pos)
        cipher = data[:44]
        auth = False
        print('[> Type "q" to exit')
        key = input('[> Input the password: ')
        if key == 'q':
            return
        try:
            aes = AESCipher(key)
            plain = aes.decrypt(cipher)
            if (plain == SECRET_SIGN):
                auth = True
                print('[> Unlock successfully ')
            else:
                print('[> Wrong password')
                os.system('pause')
        except:
            print('[> Wrong password')
            os.system('pause')

        if auth == False:
            return
        newKey = input('[> Input new password: ')
        newSign = AESCipher(newKey).encrypt(SECRET_SIGN)
        nS = int(file_size/512) + (file_size % 512 != 0)
        content = data[44:]
        for i in range(nS):
            content += self.ReadBlock(pos+i+1)

        header_data = b''
        for i in range(19):
            header_data += filename[i].encode(
                'ascii') if i < len(filename) else b'\00'
        for i in range(5):
            header_data += file_ext[i].encode(
                'ascii') if i < len(file_ext) else b'\00'

        content = AESCipher(key).decrypt(content)
        content = AESCipher(newKey).encrypt(content)
        content = bytes(newSign) + content

        file_size = len(content)

        header_data += file_size.to_bytes(4, byteorder='big') + \
            pos.to_bytes(4, byteorder='big')
        d = list(self.ReadBlock(mS))
        j = 0
        h = list(header_data)
        for i in range(id_file*32, (id_file+1)*32):
            d[i] = h[j]
            j += 1
        self.WriteBlock(mS, bytes(d))
        self.WriteBlock(pos, content)

    #Delete file
    def RemoveFile(self, id_file):
        mS = int(id_file/16) + self.sector_list_file
        data = self.ReadBlock(mS)
        id_file -= 16*(int(id_file/16))
        sector_data = data[(id_file+1)*32-4:(id_file+1)*32]
        sector_data = int.from_bytes(sector_data, byteorder='big', signed=True)
        sign = self.ReadBlock(sector_data)[:44]
        auth = False
        print('[> Type "q" to exit')
        key = input('[> Input the password: ')
        if key == 'q':
            return
        try:
            aes = AESCipher(key)
            plain = aes.decrypt(sign)
            if (plain == SECRET_SIGN):
                auth = True
                print('[> Unlock successfully ')
            else:
                print('[> Wrong password')
        except:
            print('[> Wrong password')
        if auth == False:
            return
        data = list(data)
        data[id_file*32] = 255
        self.WriteBlock(mS, bytes(data))
        print('Removed !')


def main():
    myFS = ''
    choice = 0
    os.system('cls')
    print('[> Select option below :')
    print('1. Create a volume')
    print('2. Read a volume')
    print('0. Exit')

    choice = int(input('[> '))
    if choice == 1:
        filename = input('[> Volume name: ')
        password = input('[> Password ("Enter" to set none): ')
        try:
            myFS = MyFS(filename, password)
            print('Volume create successfully ^^ ')
        except:
            print('Something went wrong')
    if choice == 2:
        filename = input('[> Volume name: ')
        if os.path.exists(filename) == False:
            print('File not exist')
            return
        try:
            myFS = MyFS(filename, mode='read')
            if myFS.auth() == False:
                choice = 0
        except:
            print('Something went wrong')
    if choice == 0:
        return

    while True:
        choice = -1
        os.system('cls')
        print('[> Select option below :')
        print('1. List all file')
        print('2. Outport a file with id')
        print('3. Import a file with name')
        print('4. Change volume password')
        print('5. Change a file password')
        print('6. Remove a file in volume')
        choice = int(input('[> '))
        if choice == 1:
            myFS.ListFiles()
        if choice == 2:
            myFS.ListFiles()
            id = int(input('[> Input file ID: '))
            myFS.ReadAfile(id)
        if choice == 3:
            file_name = input('[> Input file name: ')
            key = input('[> Input file password: ')
            myFS.AppendFile(file_name, key)
        if choice == 4:
            myFS.SetKey()
        if choice == 5:
            myFS.ListFiles()
            id = int(input('[> Input file ID: '))
            myFS.SetKeyFile(id)
        if choice == 6:
            myFS.ListFiles()
            id = int(input('[> Input file ID: '))
            myFS.RemoveFile(id)
        if choice == 0:
            print('[> Goodbye!')
            break
        os.system('pause')


if __name__ == '__main__':
    main()
