NodeMCU DEVKIT V1.0
==============

A development kit for NodeMCU firmware.

It will make NodeMCU more easy. With a micro USB cable, you can connect NodeMCU devkit to your laptop and flash it without any trouble, just like Arduino.

![DEVKIT](https://raw.githubusercontent.com/nodemcu/nodemcu-devkit-v1.0/master/Documents/NodeMCU_DEVKIT_1.0.jpg)

It is an open hardware, with ESP-12-E core [32Mbits(4MBytes) flash version].

## How to flash
- - - - - -
UPDATE
New nodemcu-flasher is released.
Bug fixed. please use latest software and re-flash.
Enjoy.
https://github.com/nodemcu/nodemcu-flasher
- - - - - -
If always have problem, please use latest flash download tool from espressif.
http://bbs.espressif.com/viewtopic.php?f=5&t=433
Please use DIO mode and 32M flash size option, and flash latest firmware to 0x00000.
Before flashing firmware, please hold FLASH button, and press RST button once.
When our firmware download tool released, it will flash firmware automatically and needn't press any button.

## Pin map

![PIN MAP](https://raw.githubusercontent.com/nodemcu/nodemcu-devkit-v1.0/master/Documents/NODEMCU_DEVKIT_V1.0_PINMAP.png)

It is designed by Altium Designer, and fully open–source. Now everyone can make their own NODEMCU.


# Starting Point

[Follow the steps in github actions](./.github/workflows/general_tests.yml)

# How To Build

* go into any project and type

```
make
```

* or just type below to build all

```
./build_all.sh
```

# How To Flash

Please type the FULL path

```
./flash.sh ./projects/get-started/hello_world
```

# How to See Output

```
miniterm.py /dev/ttyUSB0 115200
```

## What Is the Output

```
Hello world!
This is ESP8266 chip with 1 CPU cores, WiFi, silicon revision 1, 2MB external flash
Restarting in 10 seconds...
Restarting in 9 seconds...
Restarting in 8 seconds...
Restarting in 7 seconds...
Restarting in 6 seconds...
Restarting in 5 seconds...
Restarting in 4 seconds...
Restarting in 3 seconds...
Restarting in 2 seconds...
Restarting in 1 seconds...
Restarting in 0 seconds...
Restarting now.

 ets Jan  8 2013,rst cause:2, boot mode:(3,6)

load 0x40100000, len 7544, room 16
tail 8
chksum 0xc3
load 0x3ffe8408, len 24, room 0
tail 8
chksum 0x4a
load 0x3ffe8420, len 3468, room 0
tail 12
chksum 0x46
csum 0x46
␛[0;32mI (80) boot: ESP-IDF v3.4-104-g2f586ea4 2nd stage bootloader␛[0m
␛[0;32mI (80) boot: compile time 11:20:43␛[0m
␛[0;32mI (81) qio_mode: Enabling default flash chip QIO␛[0m
␛[0;32mI (97) boot: SPI Speed      : 40MHz␛[0m
␛[0;32mI (110) boot: SPI Mode       : QIO␛[0m
␛[0;32mI (122) boot: SPI Flash Size : 2MB␛[0m
␛[0;32mI (135) boot: Partition Table:␛[0m
␛[0;32mI (146) boot: ## Label            Usage          Type ST Offset   Length␛[0m
␛[0;32mI (169) boot:  0 nvs              WiFi data        01 02 00009000 00006000␛[0m
␛[0;32mI (192) boot:  1 phy_init         RF data          01 01 0000f000 00001000␛[0m
␛[0;32mI (216) boot:  2 factory          factory app      00 00 00010000 000f0000␛[0m
␛[0;32mI (239) boot: End of partition table␛[0m
␛[0;32mI (252) esp_image: segment 0: paddr=0x00010010 vaddr=0x40210010 size=0x1cc5c (117852) map␛[0m
␛[0;32mI (335) esp_image: segment 1: paddr=0x0002cc74 vaddr=0x4022cc6c size=0x06cc8 ( 27848) map␛[0m
␛[0;32mI (349) esp_image: segment 2: paddr=0x00033944 vaddr=0x3ffe8000 size=0x00544 (  1348) load␛[0m
␛[0;32mI (357) esp_image: segment 3: paddr=0x00033e90 vaddr=0x40100000 size=0x00080 (   128) load␛[0m
␛[0;32mI (385) esp_image: segment 4: paddr=0x00033f18 vaddr=0x40100080 size=0x0512c ( 20780) load␛[0m
␛[0;32mI (421) boot: Loaded app from partition at offset 0x10000␛[0m
Hello world!
This is ESP8266 chip with 1 CPU cores, WiFi, silicon revision 1, 2MB external flash
Restarting in 10 seconds...
```


# Important Links

[Standard Setup of Toolchain for Linux](https://docs.espressif.com/projects/esp8266-rtos-sdk/en/latest/get-started/linux-setup.html)

[Compiling First Project](https://docs.espressif.com/projects/esp8266-rtos-sdk/en/latest/get-started/index.html#get-started-get-esp-idf)

[Example Projects](https://github.com/espressif/ESP8266_RTOS_SDK/tree/2f586ea43f18a7d818c32b746a73e3302ad14ce2/examples)

[Node MCU Schematics](https://github.com/nodemcu/nodemcu-devkit-v1.0/blob/master/NODEMCU_DEVKIT_V1.0.PDF)

[ESP Datasheet](https://www.espressif.com/sites/default/files/documentation/0a-esp8266ex_datasheet_en.pdf)

[ESP Technical Reference](https://www.espressif.com/sites/default/files/documentation/esp8266-technical_reference_en.pdf)

[ESP Arduino Libraries](https://github.com/esp8266/Arduino/tree/master/libraries)

