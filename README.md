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
./flash.sh ./projects/protocols/sockets/tcp_server
```

# How to See Output

```
miniterm.py /dev/ttyUSB0 115200
```

## What Is the Output

```
4-104-g2f586ea4 2nd stage bootloader␛[0m
␛[0;32mI (50) boot: compile time 09:52:25␛[0m
␛[0;32mI (50) qio_mode: Enabling default flash chip QIO␛[0m
␛[0;32mI (55) boot: SPI Speed      : 40MHz␛[0m
␛[0;32mI (59) boot: SPI Mode       : QIO␛[0m
␛[0;32mI (63) boot: SPI Flash Size : 2MB␛[0m
␛[0;32mI (67) boot: Partition Table:␛[0m
␛[0;32mI (71) boot: ## Label            Usage          Type ST Offset   Length␛[0m
␛[0;32mI (78) boot:  0 nvs              WiFi data        01 02 00009000 00006000␛[0m
␛[0;32mI (85) boot:  1 phy_init         RF data          01 01 0000f000 00001000␛[0m
␛[0;32mI (93) boot:  2 factory          factory app      00 00 00010000 000f0000␛[0m
␛[0;32mI (100) boot: End of partition table␛[0m
␛[0;32mI (105) esp_image: segment 0: paddr=0x00010010 vaddr=0x40210010 size=0x566b8 (353976) map␛[0m
␛[0;32mI (234) esp_image: segment 1: paddr=0x000666d0 vaddr=0x402666c8 size=0x0f134 ( 61748) map␛[0m
␛[0;32mI (256) esp_image: segment 2: paddr=0x0007580c vaddr=0x3ffe8000 size=0x00638 (  1592) load␛[0m
␛[0;32mI (257) esp_image: segment 3: paddr=0x00075e4c vaddr=0x40100000 size=0x00080 (   128) load␛[0m
␛[0;32mI (263) esp_image: segment 4: paddr=0x00075ed4 vaddr=0x40100080 size=0x055f4 ( 22004) load␛[0m
␛[0;32mI (279) boot: Loaded app from partition at offset 0x10000␛[0m
␛[0;32mI (292) system_api: Base MAC address is not set, read default base MAC address from EFUSE␛[0m
␛[0;32mI (298) system_api: Base MAC address is not set, read default base MAC address from EFUSE␛[0m
phy_version: 1167.0, 14a6402, Feb 17 2022, 11:32:25, RTOS new
␛[0;32mI (350) phy_init: phy ver: 1167_0␛[0m
␛[0;32mI (357) example_connect: Connecting to dodo_phone...␛[0m
␛[0;32mI (2072) wifi:state: 0 -> 2 (b0)
␛[0m␛[0;32mI (2078) wifi:state: 2 -> 3 (0)
␛[0m␛[0;32mI (2083) wifi:state: 3 -> 5 (10)
␛[0m␛[0;32mI (2142) wifi:connected with dodo_phone, aid = 1, channel 6, HT20, bssid = 56:ba:19:57:da:ea
␛[0m␛[0;32mI (3065) tcpip_adapter: sta ip: 172.20.10.13, mask: 255.255.255.240, gw: 172.20.10.1␛[0m
␛[0;32mI (3070) example_connect: Connected to dodo_phone␛[0m
␛[0;32mI (3074) example_connect: IPv4 address: 172.20.10.13␛[0m
␛[0;32mI (3079) example: Socket created␛[0m
␛[0;32mI (3082) example: Socket binded␛[0m
␛[0;32mI (3086) example: Socket listening␛[0m
␛[0;32mI (403700) example: Socket accepted␛[0m
␛[0;32mI (407481) example: Received 80 bytes from 172.20.10.10:␛[0m
␛[0;32mI (407485) example: asd
␛[0m
␛[0;32mI (409617) example: Received 80 bytes from 172.20.10.10:␛[0m
␛[0;32mI (409620) example: trs
␛[0m
␛[0;32mI (413303) example: Received 80 bytes from 172.20.10.10:␛[0m
␛[0;32mI (413306) example: exit
␛[0m
␛[0;32mI (413327) example: Connection closed␛[0m
␛[0;31mE (413330) example: Shutting down socket and restarting...␛[0m
␛[0;32mI (413336) example: Socket created␛[0m
␛[0;31mE (413338) example: Socket unable to bind: errno 112␛[0m

--- exit ---
```

## How to Test

Goto tools and type

```
make
```

then edit the conf.json file. and finaly execute the below command

```
./tcp_client.exe -f conf.json
```


# Important Links

[Standard Setup of Toolchain for Linux](https://docs.espressif.com/projects/esp8266-rtos-sdk/en/latest/get-started/linux-setup.html)

[Compiling First Project](https://docs.espressif.com/projects/esp8266-rtos-sdk/en/latest/get-started/index.html#get-started-get-esp-idf)

[Example Projects](https://github.com/espressif/ESP8266_RTOS_SDK/tree/2f586ea43f18a7d818c32b746a73e3302ad14ce2/examples)

[Node MCU Schematics](https://github.com/nodemcu/nodemcu-devkit-v1.0/blob/master/NODEMCU_DEVKIT_V1.0.PDF)

[ESP Datasheet](https://www.espressif.com/sites/default/files/documentation/0a-esp8266ex_datasheet_en.pdf)

[ESP Technical Reference](https://www.espressif.com/sites/default/files/documentation/esp8266-technical_reference_en.pdf)

[ESP Arduino Libraries](https://github.com/esp8266/Arduino/tree/master/libraries)

