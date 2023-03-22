# Zad dom

## OpenWRT w quemu

## Generacja sygnału PWM

# Wejsciówka

## qemu i OpenWRT

- qemu to emulator proccessor'a
- openwrt umożliwia korzystanie z prekompilowanych binarek z możliwością doinstalowania pakietów, system operacyjny
- używa systemu plików  jffs2 i squashfs

## Programy

- sysfs - system plików udostępniający interfejs do struktur danych jądra - umożliwia sterowanie urządzeniami wpiętymi do systemu
- dd - program do kopiowania surowych danych- umożliwia kopiowanie określonej liczby bajtów lub bloków danych
- ifconfig - polecenie do konfiguracji interfeju sieciowego
- losetup - kojarzy urządzenia loop do plików lub urządzeń blokowych
    - urządzenie blokowe pozwala czytać siebie blokami
    - urządzenie pętli umożliwia dostęp do pliku jak do urządzenia blokowego

# Zadania

## OpenWRT
- co to jest
- http dla OpenWRT

## Eleketronika

### Led

$R=\frac{V_s-V_{LED}}{I_{LED}}$
$V_{LED}=2.0V$

GPIO wystawia $3.3V$
https://www.hwlibre.com/pl/gpio-raspberry-pi/

### Buzzer

- tak samo jak led, ale bez rezystora

### Przycisk



### GPIO

## GPIO

### sysfs

- `echo 27 > /sys/class/gpio/export` - zarezerwowawnie pinu 27 dla GPIO

Obsługa pinu:
    - `direction` - `[in, out, low, high]` - kierunek wejscie/wyjscie
    - `edge` -zgłoszenie przerwania
    - `echo 1 /sys/class/gpio/gpio27/value` - ustawienie wartości dla pinu

- `echo 27 > /sys/class/gpio/unexport` - zwolnienie pinu

### Python

```py
import gpio4
gpio27 = gpio4.SysfsGPIO(27)
gpio27.export = True # use the pin
gpio27.direction = 'out' # set direction to output
gpio27.value = 0 # set value to low
gpio27.value = 1 # set value to high
gpio27.export = False # cleanup
```

```py
from gpio4 import SysfsPWM
pwm = SysfsPWM(0)                   # default path: /sys/class/pwm/pwmchip0/pwm0
pwm.frequency = 1250                # set period to 1 / 1.25kHz = 800000 ns
pwm.percentage = 10                 # set duty cycle to 10% = 80000 ns
pwm.polarity = 'inversed'           # change polarity only when not enabled
pwm.enable = True 
```

## Zadania

### Zmiana led

### Płynna zmiana jasności PWM

### Buzzer

### GPIO - wejscie

### Obsługa serwomechanizmu
