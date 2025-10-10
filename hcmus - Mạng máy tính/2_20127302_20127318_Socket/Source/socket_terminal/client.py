from os import truncate
import socket
import threading

client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    
def register():
    us = input("\ninput username: ")
    client.sendall(us.encode('utf-8'))
    pa = input("\ninput password: ")
    client.sendall(pa.encode('utf-8'))
    ch = input("\ninput sign in / sign up: ")
    client.sendall(ch.encode('utf-8'))
    ch = client.recv(1024).decode('utf-8')
    if ch == 'Error1':
        print('username already exists')
        return register()
    elif ch == 'Error2':
        print('Username or password is not correct')
        return register()
    else:
        return
    
def cl():
    ip = input(str('\ninput ip '))
    p = input('\ninput port ')
    if ip == '127.0.0.1' and int(p) == 3333:
        but = input(str('\nconnect/exit: '))
        if but == 'connect':
            client.connect((str(ip),int(p)))
            register()
            def receive():
                print("\nNgân hàng nhà nước (SBV)")
                while True:
                    try:
                        print("\nCác loại tiền")
                        print("\n0 : AUD")
                        print("\n1 : CAD")
                        print("\n2 : CHF")
                        print("\n3 : EUR")
                        print("\n4 : GBP")
                        print("\n5 : JPY")
                        print("\n6 : USD")
                        c = input("Chọn loại tiền bạn muốn đổi mệnh giá: ")
                        client.sendall(c.encode('utf-8'))
                        print(client.recv(1024).decode('utf-8'))
                        print(client.recv(1024).decode('utf-8'))
                        print(client.recv(1024).decode('utf-8'))
                        
                    except:
                        print("An error occurred")
                        client.close()
                        break
        else:
            client.close()
        
        receive_thread = threading.Thread(target=receive)
        receive_thread.start()


    else:
        print('\nip or port incorrect')
        return cl()
    
cl()







        
            
             
             
            
             
             