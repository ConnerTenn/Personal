from Tkinter import *
from time import sleep
import os


master = Tk()
w = Canvas(master, width=1000, height=600)
w.delete("all")
w.pack()
w.create_line(10, 400, 10, 501)
w.create_line(0, 100, 200, 0, fill="red", dash=(4, 4))
w.create_rectangle(10, 10, 350, 350, fill="blue")
w.create_rectangle(10, 10, 100, 20, fill="blue")

mainloop()
