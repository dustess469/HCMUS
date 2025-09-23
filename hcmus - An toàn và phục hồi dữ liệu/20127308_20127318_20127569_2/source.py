import struct
import sys
import os
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
from cryptography.hazmat.primitives import padding
import datetime

from datetime import date, timedelta
import smtplib
from email.mime.multipart import MIMEMultipart
from email.mime.text import MIMEText
import time

SIZE_OF_PEOPLE = 160  # = 93 + 11 + 16 * 2 + 12 * 2

# Thêm bảng state quản lý xóa (0 - chưa dùng, 1 - đang dùng, 2 - xóa).
# Hàm ghi dữ liệu vào. Chọn dựa vào state 0 -> 2 -> 1 (thông báo full)


# Class Person
class Person:
    # Mã, Họ Tên, Ngày sinh, Ngày tham gia, Số ĐT, Số CCCD,…
    def __init__(self, id, name, birthday, join_date, phone_number, cccd):
        self.id = id
        self.name = name
        self.birthday = birthday
        self.join_date = join_date
        self.phone_number = phone_number
        self.cccd = cccd

    # Hàm in thông tin người
    def printPerson(self):
        print("ID:", self.id)
        print("Name:", self.name)
        print("Birthday:", self.birthday)
        print("Joindate:", self.join_date)
        print("Phone number:", self.phone_number)
        print("CCCD:", self.cccd)
        print("")


# Hàm tạo key AES
def generate_AES_key():
    return os.urandom(32)


# Hàm mã hóa AES
def encrypt_AES(key, plaintext):
    # Padding
    padder = padding.PKCS7(128).padder()
    padded_data = padder.update(plaintext) + padder.finalize()

    # AES Encrypt (CBC mode)
    cipher = Cipher(algorithms.AES(key), modes.ECB())
    encryptor = cipher.encryptor()
    ciphertext = encryptor.update(padded_data) + encryptor.finalize()

    return ciphertext


# Hàm giải mã AES
def decrypt_AES(key, ciphertext):
    # AES decrypt
    cipher = Cipher(algorithms.AES(key), modes.ECB())
    decryptor = cipher.decryptor()
    plaintext = decryptor.update(ciphertext) + decryptor.finalize()

    # Unpadding
    unpadder = padding.PKCS7(128).unpadder()
    data = unpadder.update(plaintext) + unpadder.finalize()

    return data


# Hàm padding
def paddingStart(data, max_len):
    data += (max_len - len(data)) * "*"
    return data


# Hàm bỏ padding
def unpaddingStart(data):
    pos = 0
    while data[pos] != "*":
        pos += 1
    data = data[0:pos]
    return data


# Ghi 1 người vào file
def write_1_People(file, People, K):
    # Ghi từng trường vào file
    padded_id = paddingStart(People.id, 15)
    id_bytes = padded_id.encode("utf-8") + b"\0"
    file.write(id_bytes)

    padded_name = paddingStart(People.name, 45)
    name_bytes = padded_name.encode("utf-8") + b"\0"
    file.write(name_bytes)

    padded_birthday = paddingStart(People.birthday, 15)
    birthday_bytes = padded_birthday.encode("utf-8") + b"\0"
    file.write(birthday_bytes)

    padded_join = paddingStart(People.join_date, 15)
    join_bytes = padded_join.encode("utf-8") + b"\0"
    file.write(join_bytes)
    # mã hóa số điện thoại và CCCD
    phone_number_bytes = (
        encrypt_AES(K, People.phone_number.encode("utf-8")).hex().encode("utf-8")
        + b"\0"
    )
    file.write(phone_number_bytes)

    cccd_bytes = (
        encrypt_AES(K, People.cccd.encode("utf-8")).hex().encode("utf-8") + b"\0"
    )
    file.write(cccd_bytes)


# Ghi file nhị phân
def writeBinary(filename, GV, SV, GV_size, reserve_size, SV_size):
    with open(filename, "wb") as file:
        # Ghi state vào file
        state = ""
        state += "1" * GV_size + reserve_size * "0" + "1" * SV_size + "0" * 10

        state_bytes = state.encode("utf-8") + b"\0"
        file.write(state_bytes)

        # Ghi Key
        K = generate_AES_key()
        file.write(K)

        # Ghi ngày tạo lập
        d = date.today()

        year = str(d.year)
        month = str(d.month)
        day = str(d.day)

        if len(day) == 1:
            day = "0" + day
        if len(month) == 1:
            month = "0" + month

        create_date = day + month + year
        file.write(create_date.encode("utf-8"))

        # Ghi kích thước mảng giáo viên vào file
        GV_size_bytes = struct.pack("i", GV_size)
        file.write(GV_size_bytes)

        # Ghi list giáo viên vào file
        for i in range(GV_size):
            write_1_People(file, GV[i], K)

        # Ghi kích thước mảng dự trữ vào file
        reserve_size_bytes = struct.pack("i", reserve_size)
        file.write(reserve_size_bytes)

        # Ghi list dự trữ rỗng vào file
        file.write(b"*" * SIZE_OF_PEOPLE * reserve_size)

        # Ghi kích thước mảng sinh viên vào file
        SV_size_bytes = struct.pack("i", SV_size)
        file.write(SV_size_bytes)

        # Ghi list sinh viên vào file
        for i in range(SV_size):
            write_1_People(file, SV[i], K)


# Đọc 1 người từ file
def read_1_People(file, K_read):
    id, name, birthday, join_date, phone_number, cccd = b"", b"", b"", b"", b"", b""
    count = 0
    # Đọc từng trường
    while count != 6:
        while True:
            char = file.read(1)
            if char == b"\0":
                break
            # Đọc id
            if count == 0:
                id += char
            # Đọc tên
            elif count == 1:
                name += char
            # Đọc birthday
            elif count == 2:
                birthday += char
            # Đọc join_date
            elif count == 3:
                join_date += char
            # Đọc phone_number
            elif count == 4:
                phone_number += char
            # Đọc CCCD
            else:
                cccd += char
        count += 1
    # Giải mã số điện thoại và CCCD
    phone_number = decrypt_AES(K_read, bytes.fromhex(phone_number.decode("utf-8")))
    cccd = decrypt_AES(K_read, bytes.fromhex(cccd.decode("utf-8")))
    return (
        unpaddingStart(id.decode("utf-8")),
        unpaddingStart(name.decode("utf-8")),
        unpaddingStart(birthday.decode("utf-8")),
        unpaddingStart(join_date.decode("utf-8")),
        phone_number.decode("utf-8"),
        cccd.decode("utf-8"),
    )


# Đọc file nhị phân
def readFile(file_path):
    with open(file_path, "rb") as file:
        # Đọc quản lý state
        state_bytes = b""
        while True:
            char = file.read(1)
            if char == b"\0":
                break
            state_bytes += char
        state_read = state_bytes.decode("utf-8")

        # Đọc key giải mã
        K_read = file.read(32)

        # Đọc ngày tạo lập
        create_date_bytes = file.read(8)
        create_date_read = create_date_bytes.decode("utf-8")

        # Đọc kích thước mảng giáo viên
        GV_size_bytes = file.read(4)  # 4 byte cho kiểu int (32-bit)
        GV_size_read = struct.unpack("i", GV_size_bytes)[0]

        # Đọc list giáo viên
        GV_read = []
        for i in range(GV_size_read):
            if state_read[i] == "1" or state_read[i] == "2":
                (
                    id_i,
                    name_i,
                    birthdate_i,
                    join_date_i,
                    phone_number_i,
                    cccd_i,
                ) = read_1_People(file, K_read)
                P = Person(
                    id_i, name_i, birthdate_i, join_date_i, phone_number_i, cccd_i
                )
                GV_read.append(P)
            else:
                file.read(SIZE_OF_PEOPLE)

        # Đọc kích thước mảng dự trữ
        reserve_size_bytes = file.read(4)
        reserve_size_read = struct.unpack("i", reserve_size_bytes)[0]

        # Đọc list dự trữ
        for i in range(reserve_size_read):
            if (
                state_read[GV_size_read + i] == "1"
                or state_read[GV_size_read + i] == "2"
            ):
                (
                    id_i,
                    name_i,
                    birthdate_i,
                    join_date_i,
                    phone_number_i,
                    cccd_i,
                ) = read_1_People(file, K_read)
                P = Person(
                    id_i, name_i, birthdate_i, join_date_i, phone_number_i, cccd_i
                )
                GV_read.append(P)
            else:
                file.read(SIZE_OF_PEOPLE)
        # Di chuyển con trỏ đến vị trí kích thước mảng sinh viên
        file.seek(
            len(state_read)
            + 1
            + 4
            + 32
            + 8
            + GV_size_read * SIZE_OF_PEOPLE
            + 4
            + reserve_size_read * SIZE_OF_PEOPLE,
            0,
        )
        SV_size_bytes = file.read(4)  # 4 byte cho kiểu int (32-bit)
        SV_size_read = struct.unpack("i", SV_size_bytes)[0]

        # Đọc list giáo viên
        SV_read = []
        for i in range(SV_size_read):
            if (
                state_read[GV_size_read + reserve_size_read + i] == "1"
                or state_read[GV_size_read + reserve_size_read + i] == "2"
            ):
                (
                    id_i,
                    name_i,
                    birthdate_i,
                    join_date_i,
                    phone_number_i,
                    cccd_i,
                ) = read_1_People(file, K_read)
                P = Person(
                    id_i, name_i, birthdate_i, join_date_i, phone_number_i, cccd_i
                )
                SV_read.append(P)
            else:
                file.read(SIZE_OF_PEOPLE)

        return (
            GV_read,
            SV_read,
            state_read,
            GV_size_read,
            reserve_size_read,
            SV_size_read,
            K_read,
        )


# Xoa tam thoi
def delete_temporary(cccd, file_name):
    (
        GV_read,
        SV_read,
        state_read,
        GV_size_read,
        reserve_size_read,
        SV_size_read,
        K_read,
    ) = readFile(file_name)
    # Trường hợp xóa giáo viên
    for i in range(len(GV_read)):
        if state_read[i] == "1" and GV_read[i].cccd == cccd:
            # print("Phan tu xoa trong mang GV")
            state_read = state_read[0:i] + "2" + state_read[i + 1 :]
            state_bytes = state_read.encode("utf-8") + b"\0"
            # mo file de ghi state vao
            with open(file_name, "rb+") as file:
                file.write(state_bytes)
            print("Xóa thành công")
            return
    # Trường hợp xóa sinh viên
    for i in range(len(SV_read)):
        if (
            state_read[i + GV_size_read + reserve_size_read] == "1"
            and SV_read[i].cccd == cccd
        ):
            # print("Phan tu xoa trong mang SV")
            state_read = (
                state_read[0 : i + GV_size_read + reserve_size_read]
                + "2"
                + state_read[i + GV_size_read + reserve_size_read + 1 :]
            )
            state_bytes = state_read.encode("utf-8") + b"\0"
            # mo file de ghi state vao
            with open(file_name, "rb+") as file:
                file.write(state_bytes)
            print("Xóa thành công")
            return

    return "CCCD khong ton tai"


# Xoa vinh vien
def delete_permanent(cccd, file_path):
    (
        GV_read,
        SV_read,
        state_read,
        GV_size_read,
        reserve_size_read,
        SV_size_read,
        K_read,
    ) = readFile(file_path)
    position = -1
    isInSV = False
    # Trường hợp xóa giáo viên
    for i in range(len(GV_read)):
        if state_read[i] == "1" and GV_read[i].cccd == cccd:
            state_read = state_read[0:i] + "0" + state_read[i + 1 :]
            position = len(state_read) + 1 + 4 + 32 + 8 + SIZE_OF_PEOPLE * i
    # Trường hợp xóa sinh viên
    for i in range(len(SV_read)):
        if (
            state_read[i + GV_size_read + reserve_size_read] == "1"
            and SV_read[i].cccd == cccd
        ):
            state_read = (
                state_read[0 : i + GV_size_read + reserve_size_read]
                + "0"
                + state_read[i + GV_size_read + reserve_size_read + 1 :]
            )
            position = (
                len(state_read)
                + 1
                + 4
                + 32
                + 8
                + SIZE_OF_PEOPLE * GV_size_read
                + 4
                + reserve_size_read * SIZE_OF_PEOPLE
                + 4
                + SIZE_OF_PEOPLE * i
            )
            isInSV = True
    #
    if position == -1:
        return "CCCD khong ton tai"
    # mo file de ghi state vào và ghi đè lại
    with open(file_path, "rb+") as file:
        state_bytes = state_read.encode("utf-8") + b"\0"
        file.write(state_bytes)
        """
        if isInSV == True:
            file.seek(len(state_read) + 1 + 4 + 32 + 8 + SIZE_OF_PEOPLE * GV_size_read
                + 4 + reserve_size_read * SIZE_OF_PEOPLE)
            SV_size_bytes = struct.pack("i", SV_size_read - 1)
            file.write(SV_size_bytes)
        """
        file.seek(position)
        file.write(
            b"*" * 15
            + b"\0"
            + b"*" * 45
            + b"\0"
            + b"*" * 15
            + b"\0"
            + b"*" * 15
            + b"\0"
            + b"*" * 32
            + b"\0"
            + b"*" * 32
            + b"\0"
        )
    print("Xóa thành công")


def delete_handle(file_name):
    print("1 - Xóa tạm thời, 2 - Xóa vĩnh viễn")
    choice = input()

    if choice == "1":
        print("Nhập CCCD của người muốn xóa: ")
        cccd = input()
        delete_temporary(cccd, file_name)
    elif choice == "2":
        print("Nhập CCCD của người muốn xóa: ")
        cccd = input()
        delete_permanent(cccd, file_name)
    else:
        print("Đầu vào không hợp lệ")
        return


# Hàm hồi phục dữ liệu
def recover_data(file_name):
    (
        GV_read,
        SV_read,
        state_read,
        GV_size_read,
        reserve_size_read,
        SV_size_read,
        K_read,
    ) = readFile(file_name)
    CCCD_choosen, index_choosen = "", 0
    temp_delete_People = []
    # Danh sách người trong thùng rác
    for i in range(len(state_read)):
        if state_read[i] == "2":
            if i < GV_size_read + reserve_size_read:
                temp_delete_People.append(GV_read[i])
            else:
                temp_delete_People.append(SV_read[i - GV_size_read - reserve_size_read])
    # In danh sách người trong thùng rác
    print("Danh sách người trong thùng rác (chọn người muốn phục hồi theo CCCD): ")
    for i in range(len(temp_delete_People)):
        temp_delete_People[i].printPerson()
    # Chọn người muốn phục hồi
    while True:
        if len(temp_delete_People) == 0:
            print("Thùng rác trống")
            return
        CCCD_choosen = input()
        flag = False
        for i in range(len(temp_delete_People)):
            if temp_delete_People[i].cccd == CCCD_choosen:
                flag = True
                break
        if flag == True:
            break
        print("CCCD không hợp lệ. Mời chọn lại")
    # Vị trí trong mảng giáo viên
    for i in range(len(GV_read)):
        if GV_read[i].cccd == CCCD_choosen:
            # index_choosen = CCCD_choosen
            index_choosen = i
    # Vị trí trong mảng sinh viên
    for i in range(len(SV_read)):
        if SV_read[i].cccd == CCCD_choosen:
            index_choosen = GV_size_read + reserve_size_read + i
    # Phục hồi
    if state_read[index_choosen] == "2":
        state_read = state_read[0:index_choosen] + "1" + state_read[index_choosen + 1 :]
        state_bytes = state_read.encode("utf-8") + b"\0"
        # mo file de ghi state vao
        with open(file_name, "rb+") as file:
            file.write(state_bytes)
        print("Phục hồi thành công")
        return

    print("Lỗi khi xóa")


# Hàm liệt kê danh sách người
def list_People(file_name):
    choose = input(
        "Bạn muốn liệt kê danh sách người (0 - Tất cả, 1 - Giáo viên, 2 - Sinh viên): "
    )

    (
        GV_read,
        SV_read,
        state_read,
        GV_size_read,
        reserve_size_read,
        SV_size_read,
        K_read,
    ) = readFile(file_name)
    # Liệt kê tất cả
    if choose == "0":
        GV_index = 0
        SV_index = 0
        for i in range(len(state_read)):
            if state_read[i] == "1":
                if i < GV_size_read + reserve_size_read:
                    GV_read[i].printPerson()
                    GV_index += 1
                else:
                    SV_read[SV_index].printPerson()
                    SV_index += 1
            elif state_read[i] == "2":
                if i < GV_size_read + reserve_size_read:
                    GV_index += 1
                else:
                    SV_index += 1
    # Liệt kê giáo viên
    elif choose == "1":
        for i in range(len(state_read)):
            if state_read[i] == "1":
                if i < GV_size_read + reserve_size_read:
                    GV_read[i].printPerson()
    # Liệt kê sinh viên
    elif choose == "2":
        for i in range(len(state_read)):
            if state_read[i] == "1":
                if i >= GV_size_read + reserve_size_read:
                    SV_read[i - GV_size_read - reserve_size_read].printPerson()


# Hàm thêm người
def add_handle(file_name):
    (
        GV_read,
        SV_read,
        state_read,
        GV_size_read,
        reserve_size_read,
        SV_size_read,
        K_read,
    ) = readFile(file_name)

    choice = 0
    print("1 - Thêm giáo viên, 2 - Thêm sinh viên: ")
    while True:
        choice = input()
        if choice == "1" or choice == "2":
            break
        print("Lựa chọn không hợp. Mời nhập lại")
    # Nhập thông tin người
    print("Nhập ID:")
    id = input()
    print("Nhập Tên:")
    name = input()
    print("Nhập Ngày sinh (day/month/year):")
    birthday = input()
    print("Nhập Ngày gia nhập (day/month/year):")
    join_date = input()
    print("Nhập số điện thoại:")
    phone_number = input()
    print("Nhập CCCD:")
    cccd = input()
    # Kiểm tra CCCD đã tồn tại chưa
    for i in range(len(GV_read)):
        if state_read[i] == "1" and GV_read[i].cccd == cccd:
            print("CCCD đã tồn tại")
            return
    # Kiểm tra CCCD đã tồn tại chưa
    for i in range(len(SV_read)):
        if (
            state_read[GV_size_read + reserve_size_read + i] == "1"
            and SV_read[i].cccd == cccd
        ):
            print("CCCD đã tồn tại")
            return
    # Tạo đối tượng người
    P = Person(id, name, birthday, join_date, phone_number, cccd)

    # Thêm giáo viên
    if choice == "1":
        if len(GV_read) < GV_size_read + reserve_size_read:
            index_choosen = -1
            # Còn vị trí trống ở trạng thái chưa sử dụng
            for i in range(GV_size_read + reserve_size_read):
                if state_read[i] == "0":
                    index_choosen = i
                    break
            # Còn vị trí trống ở trạng thái xóa tạm thời
            if index_choosen == -1:
                for i in range(GV_size_read + reserve_size_read):
                    if state_read[i] == "2":
                        index_choosen = i
                        break
            # Sửa trạng thái bảng state
            state_read = (
                state_read[0:index_choosen] + "1" + state_read[index_choosen + 1 :]
            )
            # Ghi vào file
            with open(file_name, "rb+") as file:
                state_bytes = state_read.encode("utf-8") + b"\0"
                file.write(state_bytes)
                if index_choosen < GV_size_read:
                    file.seek(
                        len(state_read)
                        + 1
                        + 32
                        + 8
                        + 4
                        + SIZE_OF_PEOPLE * index_choosen
                    )
                else:
                    file.seek(
                        len(state_read)
                        + 1
                        + 32
                        + 8
                        + 4
                        + 4
                        + SIZE_OF_PEOPLE * index_choosen
                    )
                write_1_People(file, P, K_read)
        else:
            print("Mảng giáo viên đã đầy")
            return
    if choice == "2":
        index_choosen = -1
        # Còn vị trí trống ở trạng thái chưa sử dụng
        for i in range(SV_size_read):
            if state_read[GV_size_read + reserve_size_read + i] == "0":
                index_choosen = i

        # Còn vị trí trống ở trạng thái xóa tạm thời
        if index_choosen == -1:
            for i in range(SV_size_read):
                if state_read[GV_size_read + reserve_size_read + i] == "2":
                    index_choosen = i
        # Sửa trạng thái bảng state
        state_read = (
            state_read[0 : GV_size_read + reserve_size_read + index_choosen]
            + "1"
            + state_read[GV_size_read + reserve_size_read + index_choosen + 1 :]
        )
        # Ghi vào file
        with open(file_name, "rb+") as file:
            state_bytes = state_read.encode("utf-8") + b"\0"
            file.write(state_bytes)
            file.seek(
                len(state_read)
                + 1
                + 4
                + 32
                + 8
                + SIZE_OF_PEOPLE * GV_size_read
                + 4
                + reserve_size_read * SIZE_OF_PEOPLE
            )
            SV_size_bytes = struct.pack("i", SV_size_read + 1)
            file.write(SV_size_bytes)

            file.seek(
                len(state_read)
                + 1
                + 4
                + 32
                + 8
                + SIZE_OF_PEOPLE * GV_size_read
                + 4
                + reserve_size_read * SIZE_OF_PEOPLE
                + 4
                + SIZE_OF_PEOPLE * index_choosen
            )
            write_1_People(file, P, K_read)
    return


# Hàm sửa người
def edit_handle(file_name):
    (
        GV_read,
        SV_read,
        state_read,
        GV_size_read,
        reserve_size_read,
        SV_size_read,
        K_read,
    ) = readFile(file_name)
    flag = False
    index_choosen = -1
    print("Nhập CCCD:")
    cccd = input()
    # Kiểm tra CCCD đã tồn tại chưa
    for i in range(len(GV_read)):
        if state_read[i] == "1" and GV_read[i].cccd == cccd:
            index_choosen = i
            flag = True
    # Kiểm tra CCCD đã tồn tại chưa
    for i in range(len(SV_read)):
        if (
            state_read[GV_size_read + reserve_size_read + i] == "1"
            and SV_read[i].cccd == cccd
        ):
            index_choosen = GV_size_read + reserve_size_read + i
            flag = True

    if flag == False:
        print("CCCD không tồn tại")
        return

    print("Nhập số điện thoại mới: ")
    sdt = input()
    # Ghi vào file
    with open(file_name, "rb+") as file:
        # Di chuyển con trỏ đến vị trí kích thước mảng sinh viên
        if index_choosen < GV_size_read:
            file.seek(
                len(state_read) + 1 + 4 + 32 + 8 + SIZE_OF_PEOPLE * index_choosen + 94
            )
        # Di chuyển con trỏ đến vị trí kích thước mảng dự trữ
        elif index_choosen < GV_size_read + reserve_size_read:
            file.seek(
                len(state_read)
                + 1
                + 4
                + 32
                + 8
                + SIZE_OF_PEOPLE * GV_size_read
                + 4
                + SIZE_OF_PEOPLE * (index_choosen - GV_size_read)
                + 94
            )
        # Di chuyển con trỏ đến vị trí kích thước mảng sinh viên
        else:
            file.seek(
                len(state_read)
                + 1
                + 4
                + 32
                + 8
                + SIZE_OF_PEOPLE * GV_size_read
                + 4
                + SIZE_OF_PEOPLE * reserve_size_read
                + 4
                + (index_choosen - GV_size_read - reserve_size_read) * SIZE_OF_PEOPLE
                + 94
            )
        # mã hóa số điện thoại
        phone_number_bytes = (
            encrypt_AES(K_read, sdt.encode("utf-8")).hex().encode("utf-8") + b"\0"
        )
        file.write(phone_number_bytes)


def menu():
    GV = []
    SV = []
    # Tạo đối tượng Giáo viên
    giao_vien_1 = Person(
        "GV001", "Nguyen Van A", "01/01/1980", "01/01/2010", "123456789", "123456789012"
    )
    giao_vien_2 = Person(
        "GV002", "Tran Thi B", "05/05/1985", "01/01/2015", "987654321", "987654321012"
    )
    giao_vien_3 = Person(
        "GV003", "Nguyen Van C", "10/10/1990", "01/01/2018", "111222333", "111222333444"
    )
    # Tạo đối tượng Sinh viên
    sinh_vien_1 = Person(
        "SV001", "Nguyen Van C", "10/10/1995", "01/01/2018", "111222333", "111222333444"
    )
    sinh_vien_2 = Person(
        "SV002", "Tran Thi D", "15/03/1998", "01/01/2019", "222333444", "222333444555"
    )
    sinh_vien_3 = Person(
        "SV003", "Nguyen Van E", "20/05/1999", "01/01/2019", "333444555", "333444555666"
    )
    sinh_vien_4 = Person(
        "SV004", "Tran Thi F", "25/07/2000", "01/01/2020", "444555666", "444555666777"
    )
    sinh_vien_5 = Person(
        "SV005", "Nguyen Van G", "30/09/2001", "01/01/2020", "555666777", "555666777888"
    )

    GV.append(giao_vien_1)
    GV.append(giao_vien_2)
    GV.append(giao_vien_3)

    SV.append(sinh_vien_1)
    SV.append(sinh_vien_2)
    SV.append(sinh_vien_3)
    SV.append(sinh_vien_4)
    SV.append(sinh_vien_5)
    
    writeBinary("test.dat", GV, SV, 3, 4, 5)
    ans = True
    while ans:
        os.system("cls")
        print("1. Liệt Kê")
        print("2. Thêm")
        print("3. Xóa")
        print("4. Phục Hồi Dữ Liệu")
        print("5. Sửa")
        print("0. Thoát")
        ans = input("Tác vụ muốn thực hiện ")
        os.system("cls")
        if ans == "1":
            list_People("test.dat")

        elif ans == "2":
            giao_vien_4 = Person(
                "GV004",
                "Tran Thi D",
                "15/03/1995",
                "01/01/2019",
                "222333444",
                "222333444555",
            )
            sinh_vien_6 = Person(
                "SV006",
                "Tran Thi H",
                "05/11/2002",
                "01/01/2021",
                "666777888",
                "666777888999",
            )
            add_handle("test.dat")
            print("\n Thêm thành công")

        elif ans == "3":
            delete_handle("test.dat")

        elif ans == "4":
            recover_data("test.dat")

        elif ans == "5":
            edit_handle("test.dat")
            print("\n Sửa thành công")

        elif ans == "0":
            # print("\n Goodbye")
            ans = None
        else:
            print("\n Lựa chọn không hợp lệ")
        input("Nhấn Enter để tiếp tục...")
        # os.system("pause")
    print("Tạm biệt")


def main():
    # Thông tin về tài khoản email và máy chủ SMTP
    email_address = "thanglaanh7810@gmail.com"
    email_password = "zuej vrrl wapu wnzh"
    smtp_server = "smtp.gmail.com"
    smtp_port = 587  # Đối với Gmail, sử dụng cổng 587

    # Người nhận và nội dung email
    to_address = "phanminhsang147@gmail.com"
    subject = "OTP"

    # Hàm tạo OTP theo thời gian
    def OTP():
        import time
        import random
        import math

        digits = "0123456789"
        OTP = ""
        for i in range(6):
            OTP += digits[math.floor(random.random() * 10)]
        return OTP

    # Nội dung email
    OTP = OTP()
    body = OTP

    # Tạo đối tượng MIMEMultipart
    message = MIMEMultipart()
    message["From"] = email_address
    message["To"] = to_address
    message["Subject"] = subject

    # Thêm nội dung email
    message.attach(MIMEText(body, "plain"))

    # Kết nối đến máy chủ SMTP và gửi email
    try:
        with smtplib.SMTP(smtp_server, smtp_port) as server:
            server.starttls()  # Kích hoạt chế độ TLS
            server.login(email_address, email_password)
            server.send_message(message)
        print("Email sent successfully!")
    except Exception as e:
        print("Error:", str(e))

    # Nhập OTP
    timeWait = 0
    while True:
        time.sleep(timeWait)
        otp = input("Nhập OTP: ")
        if otp == OTP:
            print("Đăng nhập thành công")
            menu()
            break
        else:
            print("Đăng nhập thất bại")
            timeWait = timeWait ^ 2 + 30


main()
