from gpio4 import SysfsGPIO
from time import sleep
from math import sin, pi
gpio27 =SysfsGPIO(21)
gpio27.export = True
gpio27.direction = 'out'
gpio27.value = 1

counter = 0
treshold = 10
t = 0
cnt = 0
while True:
	if counter < treshold:
		gpio27.value = 0
	else:
		gpio27.value = 1

	counter = (counter+1)%20	

	t += 1

gpio27.export = False
