# Lab1
## Dawid Kaszyński Mikołaj Szawerda

### Uruchomienie RPi

Do terminala UART podłączyliśmy się wykonując komendę `tio /dev/ttyUSB01`

![](img/connected.png)

Po uruchomieniu zasialania na RPi został uruchomiony system ratunkowy, zalogowaliśmy się na niego z loginem root, a następnie wykonaliśmy polecenie `udhcp`, by został przyznany adres IP

![](img/rescue_os.png)

![](img/udhcpc.png)

Sprawdzenie utworzenia podsieci między hostem a RPi.

![](img/ping_host.png)

### Kopiowanie plików

#### Test

W celu przetestowania przesyłania plików utworzyliśmy serwer http przy pomocy polecenia `python3 -m http.server`, następnie na hoscie utworzyliśmy plik testowy `foobar`, umieściliśmy go na serwerze, i na RPi pobraliśmy go korzystając z komendy `wget http://10.42.0.1:8000/foobar`

![](img/http.server.png)

![](img/wget.png)

### Kompilacja obrazu Linuxa

- po rozpakowaniu archiwum z Buildroota, wykorzystaliśmy predefiniowaną konfigurację domyślną dla RBi4 oraz uruchomiliśmy menu konfiguracji
```
make raspberrypi464defconfig
make menuconfig
```

![](img/make_menuconfig.png)

#### Wersja initramfs

Kroki:
- w meny wybranie `Toolchain --> Toolchain type: External toolchain`
- w filesystem images: zaznaczenie cpio, opcji initramfs i wyłączenie ext2/3/4, włączenie kompresji obrazu: gzip
- zapis ustawień w `.config` i urochomienie kompilacji `make`
