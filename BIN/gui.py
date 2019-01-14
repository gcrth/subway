# coding=utf-8
import turtle
import time
f = open("result.txt", "r")
str=f.read()
f.close()
route=str.split('\n')
f=open("beijing_position.txt","r")
str=f.read()
f.close()
station=str.split('\n')
station_position={}
for i in range(len(station)-1):
	str=station[i].split('\t')
	station_position[str[0]]={'x':int(str[1]),'y':int(str[2])}


turtle.screensize(945,709, "white")
turtle.bgpic(r'subway_map.png')

turtle.color("red", "yellow")
turtle.speed('slowest')
# turtle.hideturtle()

turtle.penup()
turtle.goto(station_position[route[0]]['x']-453,-station_position[route[0]]['y']+340)
turtle.pendown()
turtle.dot(10)

time.sleep(3)

for i in range(len(route)-1):
	turtle.goto(station_position[route[i]]['x']-453,-station_position[route[i]]['y']+340)
	turtle.dot(10)

turtle.mainloop()