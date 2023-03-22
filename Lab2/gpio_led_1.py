import gpio4
from time import sleep
gpio27 = gpio4.SysfsGPIO(27)
gpio27.export = True
gpio27.direction = 'out'
gpio27.value = 1
for _ in range(10):
	gpio27.value = 1
	sleep(1)
	gpio27.value = 0
	sleep(1)
gpio27.export = False
