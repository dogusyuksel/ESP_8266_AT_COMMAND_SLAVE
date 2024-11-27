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


# Important Links

[Standard Setup of Toolchain for Linux](https://docs.espressif.com/projects/esp8266-rtos-sdk/en/latest/get-started/linux-setup.html)

[Compiling First Project](https://docs.espressif.com/projects/esp8266-rtos-sdk/en/latest/get-started/index.html#get-started-get-esp-idf)

[Example Projects](https://github.com/espressif/ESP8266_RTOS_SDK/tree/2f586ea43f18a7d818c32b746a73e3302ad14ce2/examples)

[Node MCU Schematics](https://github.com/nodemcu/nodemcu-devkit-v1.0/blob/master/NODEMCU_DEVKIT_V1.0.PDF)

[ESP Datasheet](https://www.espressif.com/sites/default/files/documentation/0a-esp8266ex_datasheet_en.pdf)

[ESP Technical Reference](https://www.espressif.com/sites/default/files/documentation/esp8266-technical_reference_en.pdf)

