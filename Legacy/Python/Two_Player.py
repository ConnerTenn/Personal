#Imports
from tkinter import *

#Variables
Width=1000
Height=600
Speed=4

#Start
tk=Tk()
canvas=Canvas(tk, width=Width, height=Height)
canvas.pack()

#Functions

#Classes
class Characters:
    def Move(event):
        if event.keysym==self.Up_Key:
            canvas.move(self,0,-Speed)
            
class Player(Characters):
    def __init__(self,Player_Number, Pos_X, Pos_Y, Colour, Key_Map):
        self.Player_Number=Player_Number
        self.Pos_X=Pos_X
        self.Pos_Y=Pos_Y
        self.Colour=Colour
        for Key in Key_Map:
            if Key.upper()=='UP':
                self.Up_Key=Key_Map[Key]
            elif Key.upper()=='DOWN':
                self.Down_Key=Key_Map[Key]
            elif Key.upper()=='LEFT':
                self.Left_Key=Key_Map[Key]
            elif Key.upper()=='RIGHT':
                self.Right_Key=Key_Map[Key]

    def Move(event):
        if event.keysym==self.Up_Key:
            canvas.move(self,0,-Speed)    

#Main
Player_1=Player(1,10,10,'red',{'up':'W', 'down':'S','left':'A', 'right':'D'})
Player_2=Player(2,30,10,'blue',{'up':'Up', 'down':'Down','left':'Left', 'right':'Right'})
print('Player 1 Keys:  Up:%s Down:%s Left:%s Right:%s' % (Player_1.Up_Key, Player_1.Down_Key, Player_1.Left_Key, Player_1.Right_Key))
print('Player 2 Keys:  Up:%s Down:%s Left:%s Right:%s' % (Player_2.Up_Key, Player_2.Down_Key, Player_2.Left_Key, Player_2.Right_Key))
Player_1_Rect=canvas.create_rectangle(Player_1.Pos_X, Player_1.Pos_Y, Player_1.Pos_X+10, Player_1.Pos_Y+10, fill=Player_1.Colour)
Player_2_Rect=canvas.create_rectangle(Player_2.Pos_X, Player_2.Pos_Y, Player_2.Pos_X+10, Player_2.Pos_Y+10, fill=Player_2.Colour)

canvas.bind_all('<KeyPress>',Characters.Move)

exit
