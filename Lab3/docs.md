# Lab3

## Zadanie 1

- pobraliśmy SDK, oraz wymagany przykład w zadaniu
- w katalogu `package/` dodaliśmy przykładowy program w katologu `demo1/`
- w SDK zedytowaliśmy plik feed.confi.default dodając nasz pakiet `src-link demo1 package/demo1`
- wykonaliśmy `scripts/feeds update demo1` i `scripts/feeds install -a -p demo1`
- używając `make menuconfig` wyłączyliśmy `Select all <target>/<kernel>/<userspace> ...` oraz upewniliśmy się, że nasz nowy pakiet zostanie utworzony w wyniku wywołania kompilacji
- wywołaliśmy `make package/demo1/compile`
- przesłaliśmy otrzymany plik `.ipkg` na RPi4 i go zainstalowaliśmy `opkg install <nazwa>.ipkg`

## Zadanie 2

### Buggy
- utoworzyliśmy nowy katalog w `package/buggy`
- skopiowaliśmy `Makefile` z poprzedniego przykładu i zedytowaliśmy sekcję poświęconą komendom kompilacji
```
$(TARGET_CC) $(TARGET_CFLAGS) -o $(PKG_BUILD_DIR)/bug1.o bug1.c
$(TARGET_CC) -o $(PKG_BUILD_DIR)/bug1.o bug1.c $(PKG_BUILD_DIR)/bug1
```

- zaktualizowaliśmy zawartość `feeds.conf.default`

### Worms

- Do definicji paczki dodajemy `DEPENDS:=+libncurses`
- utworzyliśmy nowy katalog w `package/worms`
- w `Makefile` w sekcji compile najpierw tworzymy pliki pośrednie `main.o, helper.o worms.o`, a następnie linkujemy je w jeden program, linkując jednocześnie bibliotekę ncurses, dodając do definicji zależność `libncurses`

###  Uruchomienie na RPi4

- Pobieramy pliki .ipk na RPi4 za pomocą wget, a następnie instalujemy poleceniem `opkg install`.

## Debugowanie zdalne

- Instalujemy na RPi4 gdbserver oraz gdb poleceniem `opkg install`.
- Uruchamiamy serwer gdb na RPi poleceniem `gdbserver :9000 bugX`
- Na maszynie hosta uruchamiamy `./scripts/remote-gdb 10.42.0.124:9000 ./build_dir/target-aarch64_cortex-a72_musl/bugg-2.0/bugX`
- Poleceniem `directory` dodajemy katalog ze źródłami

### Debugowanie bug1

### Debugowanie bug2

### Debugowanie bug3

