import threading
import socket
import requests
import json
import time

from guiserver import *
from guiclient import *


host = '127.0.0.1'
port = 3333

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind((host,port))
server.listen()




username = []
password = []

base_url = 'https://vapi.vnappmob.com'

def get_api_key():
    while True:
        try:
            link = base_url + "/api/request_api_key?scope=exchange_rate"
            response = requests.get(link)
            return response.json()['results']
        except Exception as err:
            print(err)

def get_exchange_rate(bank_url, api_key):
    try:
        link = base_url + bank_url + "?api_key=" + api_key
        response = requests.get(link)
        return response.json()["results"]
    except Exception as err:
        print(err)

dic = get_exchange_rate("/api/v2/exchange_rate/sbv", get_api_key())



def receive():
    while True:
        try:
            client,address = server.accept()
            us = client.recv(1024).decode('utf-8')
            pa = client.recv(1024).decode('utf-8')
            ch = client.recv(1024).decode('utf-8')
            #if ch == 'sign up':
            if ch == up_bt:
                if username.count(us) == 1:
                    st = 'Error1'
                    client.send(st.encode('utf-8'))
                    return receive()
                else:
                    st = 'ok'
                    client.send(st.encode('utf-8'))
                    username.append(us)
                    password.append(pa)
                    print(f"connected with {str(address)}")
                    dic = get_exchange_rate("/api/v2/exchange_rate/sbv", get_api_key())
                    a = client.recv(1024).decode('utf-8')
                    a = int(a)
                    name = dic[a]['currency']
                    buy = dic[a]['buy']
                    sell = dic[a]['sell']
                    #send info to client
                    client.send(f'\nType of coin {name}'.encode('utf-8'))
                    client.send(f'\nBuy {buy}'.encode('utf-8'))
                    client.send(f'\nSell {sell}'.encode('utf-8'))
            
            #elif ch == 'sign in':
            elif ch == in_bt:
                if username.count(us) == 1 and username.index(us) == password.index(pa):
                    st = 'ok'
                    client.send(st.encode('utf-8'))
                    client,address = server.accept()
                    #ERROR this shit
                    print(f"connected with {str(address)}")
                    
                    dic = get_exchange_rate("/api/v2/exchange_rate/sbv", get_api_key())
                    a = client.recv(1024).decode('utf-8')
                    a = int(a)
                    name = dic[a]['currency']
                    buy = dic[a]['buy']
                    sell = dic[a]['sell']
                    client.send(f'\nType of coin {name}'.encode('utf-8'))
                    client.send(f'\nBuy {buy}'.encode('utf-8'))
                    client.send(f'\nSell {sell}'.encode('utf-8'))
                else:
                    st = 'Error2'
                    client.send(st.encode('utf-8'))
                    return receive()
                    
        except:
            receive()
            
print("Server is listening...")       
thread = threading.Thread(target=receive)
thread.start()
receive()
