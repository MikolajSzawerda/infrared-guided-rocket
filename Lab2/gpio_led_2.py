from gpio4 import SysfsGPIO
from time import sleep
from math import sin, pi
gpio27 =SysfsGPIO(27)
gpio27.export = True
gpio27.direction = 'out'
gpio27.value = 1

counter = 0
treshold = 200
t = 0
cnt = 0
while True:
	if t == 500:
		t = 0
		treshold = 500*abs(sin(cnt * pi/24))	
		cnt = (cnt + 1) % 1000000000
	if counter < treshold:
		gpio27.value = 0
	else:
		gpio27.value = 1

	counter = (counter+1)%400	

	t += 1

gpio27.export = False
