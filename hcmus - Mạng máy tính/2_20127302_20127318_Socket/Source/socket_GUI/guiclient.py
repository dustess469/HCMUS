#from guiserver import clicked
from tkinter import *
import tkinter as tk
from tkinter.ttk import *
from tkinter import messagebox



###Label first
window = Tk()

window.title("Client")
 
window.geometry('250x390')
 
hd_label = Label(window, text = "Connect to Server", font = ('', 15, 'bold')) 
hd_label.place(x=30, y=10)
 


##Enter to connect server
ip_entry = Entry(window, width = 17, justify='center')
ip_entry.place(x=68, y = 44)

port_entry = Entry(window, width = 11, justify='center')
port_entry.place(x=85, y = 70)



##Button to conntact server
window.resizable(False, False)
#connect-disconnect
def clicked():
    user_entry.configure(state='normal')
    pass_entry.configure(state='normal')
    in_bt.configure(state='normal')
    up_bt.configure(state='normal')
    messagebox.showinfo('Notification', 'Connected server')


cnt_bt = Button(window, text="Connect", command=clicked)
cnt_bt.place(x=19, y=100)

discnt_bt = Button(window, text="Disconnect")
discnt_bt.place(x=149, y=100)



##Login
lg_label = Label(window, text = "Login", font = ('', 15, 'bold')) 
lg_label.place(x=100, y=140)

user_label = Label(window, text = "Username:")
user_label.place(x=10, y=175)
user_entry = Entry(window, width = 19, state='disabled')
user_entry.place(x=80, y=175)

pass_label = Label(window, text = "Passwword:")
pass_label.place(x=10, y=205)
pass_entry = Entry(window, width = 19, state='disabled')
pass_entry.place(x=80, y=205)




##click-sign in
def click():
    current_cb.configure(state='normal')
    wcur_entry.configure(state='normal')
    search_bt.configure(state='normal')
    messagebox.showinfo('Notification', 'Registered successfully')

def clickt():
    messagebox.showinfo('Notification', 'Username or password is incorrect')  

#signin-singup    
in_bt=Button(window, text = "Sign in",state='disable', command=clickt)
in_bt.place(x=19, y=240)


up_bt = Button(window, text = "Sign up", state= 'disable', command=click)
up_bt.place(x=149, y=240)




###search
current_lb = Label(window, text = "Current:")
current_lb.place(x=5, y=290)
current_cb = Combobox(window, state='disable')
current_cb['values']= ("0 : AUD", "1 : CAD", "2 : CHF", "3 : EUR", "4 : GBP", "5 : JPY", "6 : USD")
current_cb.current(0)
current_cb.place(x=70, y=290)

wcur_lb = Label(window, text="Current want to change:")
wcur_lb.place(x=5, y=320)
wcur_entry = Entry(window, width=7, state='disable')
wcur_entry.place(x=165, y=320)

def clickes():
    messagebox.showinfo('Notification', '\nType of coin')
search_bt=Button(window, text = "Search", state='disable', command=clickes)
search_bt.place(x=150, y=350)

window.mainloop()