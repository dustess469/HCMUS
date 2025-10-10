from tkinter import *
import tkinter as tk
from tkinter.ttk import *
from tkinter import ttk
from tkinter import scrolledtext
 
window = Tk()
 
window.title("Server")
 
window.geometry('450x200')
 

#Server Infomation
hd_lb = Label(window, text = "Server Infomation", font = ('', 13, 'bold')) 
hd_lb.place(x=10, y=10)
 
name_ip = Label(window, text = "IP:")
name_ip.place(x=0, y=40)
var_ip=tk.StringVar()
var_ip.set('127.0.0.1')
txt_ip = Entry(window, width = 23, textvariable=var_ip)
txt_ip.place(x=50, y=40)

name_port = Label(window, text = "PORT:")
name_port.place(x=0, y=70)
var_port=tk.StringVar()
var_port.set('3333')
txt_port = Entry(window, width = 23, textvariable=var_port)
txt_port.place(x=50, y=70)

bank_lb = Label(window, text = "BANK:")
bank_lb.place(x=0, y=100)
bank_cb = Combobox(window)
bank_cb['values']= ("SBV")
bank_cb.current(0)
bank_cb.place(x=50, y=100)

lbl = Label(window, text="")
lbl.place(x=50, y=160)
def clicket():
    lbl.configure(text="Server is listening...",font = ('', 10, 'bold') )
    bank_lb.configure(state='normal')
start_bt = Button(window, text="Start Server", command=clicket)
start_bt.place(x=120, y=130)



#server client
svlist_lb=Label(window, text= "Server List",font = ('', 13, 'bold') )
svlist_lb.place(x=250, y=10)
list_tx = Text(window,width=20,height=8, state='disable')
list_tx.place(x=250, y=40)



window.mainloop()