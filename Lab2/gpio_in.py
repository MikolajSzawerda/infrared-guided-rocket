import gpio4

gpioB = gpio4.SysfsGPIO(18)
gpioLED = gpio4.SysfsGPIO(27)
gpioLED.export = True
gpioLED.direction = 'out'
gpioB.export = True
gpioB.direction = 'in'

while True: gpioLED.value = int(not gpioB.value)
		


