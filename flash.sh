#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo "please type project name with path, eg: './projects/system/factory-test'"
    exit 1
fi

if [ "$#" -eq 1 ]; then
    if [[ $1 == *"-h"* ]]; then
        echo "please type project name with path, eg: SEE BELOW"
        cd projects

        files=$(find . -iname 'makefile')
        while IFS= read -r line; do
            echo "    >> ./peripherals/$line"
        done <<< "$files"

        cd -

        exit 0
    fi
fi
esp_flasher="$IDF_PATH/components/esptool_py/esptool/esptool.py"
flasher_options="--chip esp8266 --port /dev/ttyUSB0 --baud 115200 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m"
single_app_add_and_bin="0x8000 $1/build/partitions_singleapp.bin"
bootloader_add_and_bin="0x0 $1/build/bootloader/bootloader.bin"
actual_project_name=$(echo $1 | rev | cut -d/ -f1 | rev)
actual_fw_add_and_bin="0x10000 $1/build/$actual_project_name.bin"


if [[ $1 == *"./projects/system/factory-test"* ]]; then
    python $esp_flasher $flasher_options --flash_size 2MB 0xd000 $1/build/ota_data_initial.bin $bootloader_add_and_bin 0x10000 $1/build/factory-test.bin 0x8000 $1/build/partitions_two_ota.bin
elif [[ $1 == *"./projects/system/ota/native_ota/2+MB_flash/new_to_new_with_old"* ]]; then
    python $esp_flasher $flasher_options --flash_size 2MB 0xd000 $1/build/ota_data_initial.bin $bootloader_add_and_bin 0x10000 $1/build/ota.bin 0x8000 $1/build/partitions_two_ota_v2tov3.2MB.bin
elif [[ $1 == *"./projects/system/ota/native_ota/2+MB_flash/new_to_new_no_old"* ]]; then
    python $esp_flasher $flasher_options --flash_size 2MB 0xd000 $1/build/ota_data_initial.bin $bootloader_add_and_bin 0x10000 $1/build/ota.bin 0x8000 $1/build/partitions_two_ota.bin
elif [[ $1 == *"./projects/system/ota/native_ota/1MB_flash/new_to_new_with_old"* ]]; then
    python $esp_flasher $flasher_options --flash_size 1MB 0x83000 $1/build/ota_data_initial.bin $bootloader_add_and_bin 0x7000 $1/build/ota.bin 0x5000 $1/build/partitions_two_ota_v2tov3.1MB.bin
elif [[ $1 == *"./projects/system/ota/native_ota/1MB_flash/new_to_new_no_old_copy"* ]]; then
    python $esp_flasher $flasher_options --flash_size 1MB 0xd000 $1/build/ota_data_initial.bin $bootloader_add_and_bin 0x10000 $1/build/ota.bin 0x8000 $1/build/partitions_two_ota.1MB.bin
elif [[ $1 == *"./projects/system/ota/native_ota/1MB_flash/new_to_new_no_old"* ]]; then
    python $esp_flasher $flasher_options --flash_size 1MB 0xd000 $1/build/ota_data_initial.bin $bootloader_add_and_bin 0x10000 $1/build/ota.bin 0x8000 $1/build/partitions_two_ota.1MB.bin
elif [[ $1 == *"./projects/system/ota/simple_ota_example"* ]]; then
    python $esp_flasher $flasher_options --flash_size 4MB 0xd000 $1/build/ota_data_initial.bin $bootloader_add_and_bin 0x10000 $1/build/simple_ota.bin 0x8000 $1/build/partitions_two_ota.bin
elif [[ $1 == *"./projects/system/console"* ]]; then
    python $esp_flasher $flasher_options --flash_size 2MB $bootloader_add_and_bin $actual_fw_add_and_bin 0x8000 $1/build/partitions_example.bin
elif [[ $1 == *"./projects/storage/spiffs"* ]]; then
    python $esp_flasher $flasher_options --flash_size 2MB $bootloader_add_and_bin $actual_fw_add_and_bin 0x8000 $1/build/partitions_example.bin
else
    python $esp_flasher $flasher_options --flash_size 2MB $bootloader_add_and_bin $actual_fw_add_and_bin $single_app_add_and_bin
fi
exit 0
