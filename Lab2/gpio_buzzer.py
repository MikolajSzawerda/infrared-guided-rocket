from gpio4 import SysfsGPIO
from time import sleep
from math import sin, pi, fmod
gpioB = SysfsGPIO(13)
gpioB.export = True
gpioB.direction = 'out'
gpioB.value = 1

counter = 0
treshold = 5
t = 0
cnt = 0
notes = [
65.41, 73.42, 82.41, 87.31, 98.0, 110.0, 123.47, 130.81, 146.83, 164.81,
174.61, 196.0, 220.0, 246.94
]
period = notes[0]
treshold = period/2
while True:
	if t == 10000:
		t = 0
		period = 100/notes[cnt]
		treshold = period/2
		cnt = (cnt + 1) % len(notes)
	if counter < treshold:
		gpioB.value = 0
	else:
		gpioB.value = 1

	counter = fmod(counter+0.1, period)
	t += 1

gpio27.export = False
