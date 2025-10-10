from os import truncate
import socket
import threading
import tkinter

from guiclient import *

client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    
def register():
    #us = input("\nNhap username: ")
    us= input(user_entry)
    client.sendall(us.encode('utf-8'))

    #pa = input("\nNhap password: ")
    pa=input(pass_entry)
    client.sendall(pa.encode('utf-8'))

    #ch = input("\nNhap sign in de dang nhap / sign up de dang ki: ")
    ch = input(in_bt, up_bt)
    client.sendall(ch.encode('utf-8'))
    ch = client.recv(1024).decode('utf-8')
    if ch == 'Error1':
        print('User name da ton tai')
        return register()
    elif ch == 'Error2':
        print('User name hoac pass khong dung')
        return register()
    else:
        return
    
def cl():
    #ip = input(str('\ninput ip '))
    ip = input(ip_entry)
    #p = input('\nInput port ')
    p = input(port_entry)
    if ip == '127.0.0.1' and int(p) == 3333:
        client.connect((str(ip),int(p)))
        register()
        #but = input(str('\nConnect/exit: '))
        but = input(cnt_bt, discnt_bt)
        #if but == 'Connect':
        if but == cnt_bt:
            def receive():
                #print("\nNgân hàng nhà nước (SBV)")
                while True:
                    try:
                        #print("\nCác loại tiền")
                        #print("\n0 : AUD")
                        #print("\n1 : CAD")
                        #print("\n2 : CHF")
                        #print("\n3 : EUR")
                        #print("\n4 : GBP")
                        #print("\n5 : JPY")
                        #print("\n6 : USD")
                        
                        #c = input("Chọn loại tiền bạn muốn đổi mệnh giá: ")
                        c = input(wcur_entry)
                        client.sendall(c.encode('utf-8'))
                        #print info server to client
                        print(client.recv(1024).decode('utf-8'))
                        print(client.recv(1024).decode('utf-8'))
                        print(client.recv(1024).decode('utf-8'))
                        
                    except:
                        #print("An error occurred")
                        client.close()
                        break
        else:
            discnt_bt
            client.close()
        
        receive_thread = threading.Thread(target=receive)
        receive_thread.start()


    else:
        print('\nIp or port incorrect')
        return cl()
    
cl()
