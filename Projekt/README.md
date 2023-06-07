## Install OpenWRT

```shell
wget -O openwrt.tar.xz https://downloads.openwrt.org/releases/21.02.1/targets/bcm27xx/bcm2711/openwrt-sdk-21.02.1-bcm27xx-bcm2711_gcc-8.4.0_musl.Linux-x86_64.tar.xz
tar -xf openwrt.tar.xz
```

## Make link

```shell
ln -s ../../../thermo_guide thermo_guide 
```

## Preconfig openwrt

### Feeds.conf.default
```
src-link thermo_guide package/thermo_guide/src
```

### Config

```shell
scripts/feeds update -a
scripts/feeds install -p thermo_guide -a 
make menuconfig
```

Global Build Settings wyłaczyć opcje:
Select all target specific packages by default
Select all kernel module packages by default
Select all userspace packages by default
Cryptographically sign package lists

Advanced configuration options wskazane jest wyłaczenie opcji
Automatic removal of build directories

Dodać pakiet w do budowania

### Budowanie

```shell
make package/thermo_guide/compile -j4
```

```shell
make package/thermo_guide/compile -j1 V=s
```

## Na openwrt

```shell
/etc/init.d/firewall stop
```

### config.txt
```
dtoverlay=pwm-2chan,pin=12,func=4,pin2=13,func2=4
dtoverlay=i2c1
```

### Install

```shell
kmod-i2c-bcm2835
kmod-pwm-bcm2835
```