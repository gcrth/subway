# coding=utf-8
import turtle
f = open("result.txt", "r")
str=f.read()

turtle.screensize(945,709, "white")
turtle.bgpic(r'subway_map.png')

turtle.color("red", "yellow")
turtle.speed('slowest')
# turtle.hideturtle()

turtle.penup()

turtle.dot(10)






turtle.mainloop()