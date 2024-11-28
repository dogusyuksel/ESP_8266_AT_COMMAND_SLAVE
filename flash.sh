#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo "please type project name with path, eg: './projects/system/factory-test'"
    exit 1
fi

if [ "$#" -eq 1 ]; then
    if [[ $1 == *"-h"* ]]; then
        echo "please type project name with path, eg: './projects/system/factory-test'"
        exit 0
    fi
fi

if [[ $1 == *"./projects/system/factory-test"* ]]; then
    python $IDF_PATH/components/esptool_py/esptool/esptool.py --chip esp8266 --port /dev/ttyUSB0 --baud 115200 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size 2MB 0xd000 $1/build/ota_data_initial.bin 0x0 $1/build/bootloader/bootloader.bin 0x10000 $1/build/factory-test.bin 0x8000 $1/build/partitions_two_ota.bin
elif [[ $1 == *"./projects/system/ota/native_ota/2+MB_flash/new_to_new_with_old"* ]]; then
    python $IDF_PATH/components/esptool_py/esptool/esptool.py --chip esp8266 --port /dev/ttyUSB0 --baud 115200 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size 2MB 0xd000 $1/build/ota_data_initial.bin 0x0 $1/build/bootloader/bootloader.bin 0x10000 $1/build/ota.bin 0x8000 $1/build/partitions_two_ota_v2tov3.2MB.bin
elif [[ $1 == *"./projects/system/ota/native_ota/2+MB_flash/new_to_new_no_old"* ]]; then
    python $IDF_PATH/components/esptool_py/esptool/esptool.py --chip esp8266 --port /dev/ttyUSB0 --baud 115200 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size 2MB 0xd000 $1/build/ota_data_initial.bin 0x0 $1/build/bootloader/bootloader.bin 0x10000 $1/build/ota.bin 0x8000 $1/build/partitions_two_ota.bin
elif [[ $1 == *"./projects/system/ota/native_ota/1MB_flash/new_to_new_with_old"* ]]; then
    python $IDF_PATH/components/esptool_py/esptool/esptool.py --chip esp8266 --port /dev/ttyUSB0 --baud 115200 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size 1MB 0x83000 $1/build/ota_data_initial.bin 0x0 $1/build/bootloader/bootloader.bin 0x7000 $1/build/ota.bin 0x5000 $1/build/partitions_two_ota_v2tov3.1MB.bin
elif [[ $1 == *"./projects/system/ota/native_ota/1MB_flash/new_to_new_no_old_copy"* ]]; then
    python $IDF_PATH/components/esptool_py/esptool/esptool.py --chip esp8266 --port /dev/ttyUSB0 --baud 115200 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size 1MB 0xd000 $1/build/ota_data_initial.bin 0x0 $1/build/bootloader/bootloader.bin 0x10000 $1/build/ota.bin 0x8000 $1/build/partitions_two_ota.1MB.bin
elif [[ $1 == *"./projects/system/ota/native_ota/1MB_flash/new_to_new_no_old"* ]]; then
    python $IDF_PATH/components/esptool_py/esptool/esptool.py --chip esp8266 --port /dev/ttyUSB0 --baud 115200 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size 1MB 0xd000 $1/build/ota_data_initial.bin 0x0 $1/build/bootloader/bootloader.bin 0x10000 $1/build/ota.bin 0x8000 $1/build/partitions_two_ota.1MB.bin
elif [[ $1 == *"./projects/system/ota/simple_ota_example"* ]]; then
    python $IDF_PATH/components/esptool_py/esptool/esptool.py --chip esp8266 --port /dev/ttyUSB0 --baud 115200 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size 4MB 0xd000 $1/build/ota_data_initial.bin 0x0 $1/build/bootloader/bootloader.bin 0x10000 $1/build/simple_ota.bin 0x8000 $1/build/partitions_two_ota.bin
elif [[ $1 == *"./projects/system/console"* ]]; then
    python $IDF_PATH/components/esptool_py/esptool/esptool.py --chip esp8266 --port /dev/ttyUSB0 --baud 115200 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size 2MB 0x0 $1/build/bootloader/bootloader.bin 0x10000 $1/build/console.bin 0x8000 $1/build/partitions_example.bin
elif [[ $1 == *"./projects/protocols/openssl_client"* ]]; then
    python $IDF_PATH/components/esptool_py/esptool/esptool.py --chip esp8266 --port /dev/ttyUSB0 --baud 115200 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size 2MB 0x0 $1/build/bootloader/bootloader.bin 0x10000 $1/build/openssl_client.bin 0x8000 $1/build/partitions_singleapp.bin
elif [[ $1 == *"./projects/protocols/modbus/tcp/mb_tcp_slave"* ]]; then
    python $IDF_PATH/components/esptool_py/esptool/esptool.py --chip esp8266 --port /dev/ttyUSB0 --baud 115200 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size 2MB 0x0 $1/build/bootloader/bootloader.bin 0x10000 $1/build/modbus_tcp_slave.bin 0x8000 $1/build/partitions_singleapp.bin
elif [[ $1 == *"./projects/protocols/modbus/tcp/mb_tcp_master"* ]]; then
    python $IDF_PATH/components/esptool_py/esptool/esptool.py --chip esp8266 --port /dev/ttyUSB0 --baud 115200 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size 2MB 0x0 $1/build/bootloader/bootloader.bin 0x10000 $1/build/modbus_tcp_master.bin 0x8000 $1/build/partitions_singleapp.bin
elif [[ $1 == *"./projects/protocols/icmp_echo"* ]]; then
    python $IDF_PATH/components/esptool_py/esptool/esptool.py --chip esp8266 --port /dev/ttyUSB0 --baud 115200 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size 2MB 0x0 $1/build/bootloader/bootloader.bin 0x10000 $1/build/icmp-echo.bin 0x8000 $1/build/partitions_singleapp.bin
elif [[ $1 == *"./projects/protocols/mqtt/ssl_psk"* ]]; then
    python $IDF_PATH/components/esptool_py/esptool/esptool.py --chip esp8266 --port /dev/ttyUSB0 --baud 115200 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size 2MB 0x0 $1/build/bootloader/bootloader.bin 0x10000 $1/build/mqtt_ssl_psk.bin 0x8000 $1/build/partitions_singleapp.bin
elif [[ $1 == *"./projects/protocols/mqtt/ws"* ]]; then
    python $IDF_PATH/components/esptool_py/esptool/esptool.py --chip esp8266 --port /dev/ttyUSB0 --baud 115200 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size 2MB 0x0 $1/build/bootloader/bootloader.bin 0x10000 $1/build/mqtt_websocket.bin 0x8000 $1/build/partitions_singleapp.bin
elif [[ $1 == *"./projects/protocols/mqtt/wss"* ]]; then
    python $IDF_PATH/components/esptool_py/esptool/esptool.py --chip esp8266 --port /dev/ttyUSB0 --baud 115200 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size 2MB 0x0 $1/build/bootloader/bootloader.bin 0x10000 $1/build/mqtt_websocket_secure.bin 0x8000 $1/build/partitions_singleapp.bin
elif [[ $1 == *"./projects/protocols/mqtt/ssl"* ]]; then
    python $IDF_PATH/components/esptool_py/esptool/esptool.py --chip esp8266 --port /dev/ttyUSB0 --baud 115200 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size 2MB 0x0 $1/build/bootloader/bootloader.bin 0x10000 $1/build/mqtt_ssl.bin 0x8000 $1/build/partitions_singleapp.bin
elif [[ $1 == *"./projects/protocols/mqtt/ssl_mutual_auth"* ]]; then
    python $IDF_PATH/components/esptool_py/esptool/esptool.py --chip esp8266 --port /dev/ttyUSB0 --baud 115200 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size 2MB 0x0 $1/build/bootloader/bootloader.bin 0x10000 $1/build/mqtt_ssl_mutual_auth.bin 0x8000 $1/build/partitions_singleapp.bin
elif [[ $1 == *"./projects/protocols/mqtt/tcp"* ]]; then
    python $IDF_PATH/components/esptool_py/esptool/esptool.py --chip esp8266 --port /dev/ttyUSB0 --baud 115200 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size 2MB 0x0 $1/build/bootloader/bootloader.bin 0x10000 $1/build/mqtt_tcp.bin 0x8000 $1/build/partitions_singleapp.bin
elif [[ $1 == *"./projects/protocols/mdns"* ]]; then
    python $IDF_PATH/components/esptool_py/esptool/esptool.py --chip esp8266 --port /dev/ttyUSB0 --baud 115200 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size 2MB 0x0 $1/build/bootloader/bootloader.bin 0x10000 $1/build/mdns-test.bin 0x8000 $1/build/partitions_singleapp.bin
elif [[ $1 == *"./projects/protocols/https_mbedtls"* ]]; then
    python $IDF_PATH/components/esptool_py/esptool/esptool.py --chip esp8266 --port /dev/ttyUSB0 --baud 115200 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size 2MB 0x0 $1/build/bootloader/bootloader.bin 0x10000 $1/build/https-mbedtls.bin 0x8000 $1/build/partitions_singleapp.bin
elif [[ $1 == *"./projects/protocols/http_request"* ]]; then
    python $IDF_PATH/components/esptool_py/esptool/esptool.py --chip esp8266 --port /dev/ttyUSB0 --baud 115200 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size 2MB 0x0 $1/build/bootloader/bootloader.bin 0x10000 $1/build/http-request.bin 0x8000 $1/build/partitions_singleapp.bin
elif [[ $1 == *"./projects/protocols/sntp"* ]]; then
    python $IDF_PATH/components/esptool_py/esptool/esptool.py --chip esp8266 --port /dev/ttyUSB0 --baud 115200 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size 2MB 0x0 $1/build/bootloader/bootloader.bin 0x10000 $1/build/sntp.bin 0x8000 $1/build/partitions_singleapp.bin
elif [[ $1 == *"./projects/protocols/coap_client"* ]]; then
    python $IDF_PATH/components/esptool_py/esptool/esptool.py --chip esp8266 --port /dev/ttyUSB0 --baud 115200 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size 2MB 0x0 $1/build/bootloader/bootloader.bin 0x10000 $1/build/coap_client.bin 0x8000 $1/build/partitions_singleapp.bin
elif [[ $1 == *"./projects/protocols/http_server/persistent_sockets"* ]]; then
    python $IDF_PATH/components/esptool_py/esptool/esptool.py --chip esp8266 --port /dev/ttyUSB0 --baud 115200 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size 2MB 0x0 $1/build/bootloader/bootloader.bin 0x10000 $1/build/persistent_sockets.bin 0x8000 $1/build/partitions_singleapp.bin
elif [[ $1 == *"./projects/protocols/http_server/simple"* ]]; then
    python $IDF_PATH/components/esptool_py/esptool/esptool.py --chip esp8266 --port /dev/ttyUSB0 --baud 115200 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size 2MB 0x0 $1/build/bootloader/bootloader.bin 0x10000 $1/build/simple.bin 0x8000 $1/build/partitions_singleapp.bin
elif [[ $1 == *"./projects/protocols/http_server/advanced_tests"* ]]; then
    python $IDF_PATH/components/esptool_py/esptool/esptool.py --chip esp8266 --port /dev/ttyUSB0 --baud 115200 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size 2MB 0x0 $1/build/bootloader/bootloader.bin 0x10000 $1/build/tests.bin 0x8000 $1/build/partitions_singleapp.bin
elif [[ $1 == *"./projects/protocols/coap_server"* ]]; then
    python $IDF_PATH/components/esptool_py/esptool/esptool.py --chip esp8266 --port /dev/ttyUSB0 --baud 115200 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size 2MB 0x0 $1/build/bootloader/bootloader.bin 0x10000 $1/build/coap_server.bin 0x8000 $1/build/partitions_singleapp.bin
elif [[ $1 == *"./projects/protocols/sockets/tcp_server"* ]]; then
    python $IDF_PATH/components/esptool_py/esptool/esptool.py --chip esp8266 --port /dev/ttyUSB0 --baud 115200 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size 2MB 0x0 $1/build/bootloader/bootloader.bin 0x10000 $1/build/tcp_server.bin 0x8000 $1/build/partitions_singleapp.bin
elif [[ $1 == *"./projects/protocols/sockets/udp_server"* ]]; then
    python $IDF_PATH/components/esptool_py/esptool/esptool.py --chip esp8266 --port /dev/ttyUSB0 --baud 115200 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size 2MB 0x0 $1/build/bootloader/bootloader.bin 0x10000 $1/build/udp_server.bin 0x8000 $1/build/partitions_singleapp.bin
elif [[ $1 == *"./projects/protocols/sockets/udp_client"* ]]; then
    python $IDF_PATH/components/esptool_py/esptool/esptool.py --chip esp8266 --port /dev/ttyUSB0 --baud 115200 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size 2MB 0x0 $1/build/bootloader/bootloader.bin 0x10000 $1/build/udp_client.bin 0x8000 $1/build/partitions_singleapp.bin
elif [[ $1 == *"./projects/protocols/sockets/tcp_client"* ]]; then
    python $IDF_PATH/components/esptool_py/esptool/esptool.py --chip esp8266 --port /dev/ttyUSB0 --baud 115200 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size 2MB 0x0 $1/build/bootloader/bootloader.bin 0x10000 $1/build/tcp_client.bin 0x8000 $1/build/partitions_singleapp.bin
elif [[ $1 == *"./projects/protocols/sockets/udp_multicast"* ]]; then
    python $IDF_PATH/components/esptool_py/esptool/esptool.py --chip esp8266 --port /dev/ttyUSB0 --baud 115200 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size 2MB 0x0 $1/build/bootloader/bootloader.bin 0x10000 $1/build/udp-multicast.bin 0x8000 $1/build/partitions_singleapp.bin
elif [[ $1 == *"./projects/protocols/esp_http_client"* ]]; then
    python $IDF_PATH/components/esptool_py/esptool/esptool.py --chip esp8266 --port /dev/ttyUSB0 --baud 115200 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size 2MB 0x0 $1/build/bootloader/bootloader.bin 0x10000 $1/build/esp-http-client-example.bin 0x8000 $1/build/partitions_singleapp.bin
elif [[ $1 == *"./projects/protocols/openssl_server"* ]]; then
    python $IDF_PATH/components/esptool_py/esptool/esptool.py --chip esp8266 --port /dev/ttyUSB0 --baud 115200 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size 2MB 0x0 $1/build/bootloader/bootloader.bin 0x10000 $1/build/openssl-server.bin 0x8000 $1/build/partitions_singleapp.bin
elif [[ $1 == *"./projects/protocols/openssl_demo"* ]]; then
    python $IDF_PATH/components/esptool_py/esptool/esptool.py --chip esp8266 --port /dev/ttyUSB0 --baud 115200 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size 2MB 0x0 $1/build/bootloader/bootloader.bin 0x10000 $1/build/openssl_demo.bin 0x8000 $1/build/partitions_singleapp.bin
elif [[ $1 == *"./projects/protocols/https_request"* ]]; then
    python $IDF_PATH/components/esptool_py/esptool/esptool.py --chip esp8266 --port /dev/ttyUSB0 --baud 115200 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size 2MB 0x0 $1/build/bootloader/bootloader.bin 0x10000 $1/build/https_request.bin 0x8000 $1/build/partitions_singleapp.bin
elif [[ $1 == *"./projects/peripherals/i2s"* ]]; then
    python $IDF_PATH/components/esptool_py/esptool/esptool.py --chip esp8266 --port /dev/ttyUSB0 --baud 115200 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size 2MB 0x0 $1/build/bootloader/bootloader.bin 0x10000 $1/build/i2s.bin 0x8000 $1/build/partitions_singleapp.bin
elif [[ $1 == *"./projects/peripherals/pwm"* ]]; then
    python $IDF_PATH/components/esptool_py/esptool/esptool.py --chip esp8266 --port /dev/ttyUSB0 --baud 115200 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size 2MB 0x0 $1/build/bootloader/bootloader.bin 0x10000 $1/build/pwm.bin 0x8000 $1/build/partitions_singleapp.bin
elif [[ $1 == *"./projects/peripherals/spi/normal_performance/spi_master"* ]]; then
    python $IDF_PATH/components/esptool_py/esptool/esptool.py --chip esp8266 --port /dev/ttyUSB0 --baud 115200 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size 2MB 0x0 $1/build/bootloader/bootloader.bin 0x10000 $1/build/spi_master.bin 0x8000 $1/build/partitions_singleapp.bin
elif [[ $1 == *"./projects/peripherals/spi/normal_performance/spi_slave"* ]]; then
    python $IDF_PATH/components/esptool_py/esptool/esptool.py --chip esp8266 --port /dev/ttyUSB0 --baud 115200 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size 2MB 0x0 $1/build/bootloader/bootloader.bin 0x10000 $1/build/spi_slave.bin 0x8000 $1/build/partitions_singleapp.bin
elif [[ $1 == *"./projects/peripherals/spi/high_performance/spi_master"* ]]; then
    python $IDF_PATH/components/esptool_py/esptool/esptool.py --chip esp8266 --port /dev/ttyUSB0 --baud 115200 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size 2MB 0x0 $1/build/bootloader/bootloader.bin 0x10000 $1/build/spi_master.bin 0x8000 $1/build/partitions_singleapp.bin
elif [[ $1 == *"./projects/peripherals/spi/high_performance/spi_slave"* ]]; then
    python $IDF_PATH/components/esptool_py/esptool/esptool.py --chip esp8266 --port /dev/ttyUSB0 --baud 115200 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size 2MB 0x0 $1/build/bootloader/bootloader.bin 0x10000 $1/build/spi_slave.bin 0x8000 $1/build/partitions_singleapp.bin
elif [[ $1 == *"./projects/peripherals/adc"* ]]; then
    python $IDF_PATH/components/esptool_py/esptool/esptool.py --chip esp8266 --port /dev/ttyUSB0 --baud 115200 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size 2MB 0x0 $1/build/bootloader/bootloader.bin 0x10000 $1/build/adc_example.bin 0x8000 $1/build/partitions_singleapp.bin
elif [[ $1 == *"./projects/peripherals/ir_rx"* ]]; then
    python $IDF_PATH/components/esptool_py/esptool/esptool.py --chip esp8266 --port /dev/ttyUSB0 --baud 115200 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size 2MB 0x0 $1/build/bootloader/bootloader.bin 0x10000 $1/build/ir_rx.bin 0x8000 $1/build/partitions_singleapp.bin
elif [[ $1 == *"./projects/peripherals/ir_tx"* ]]; then
    python $IDF_PATH/components/esptool_py/esptool/esptool.py --chip esp8266 --port /dev/ttyUSB0 --baud 115200 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size 2MB 0x0 $1/build/bootloader/bootloader.bin 0x10000 $1/build/ir.bin 0x8000 $1/build/partitions_singleapp.bin
elif [[ $1 == *"./projects/peripherals/ledc"* ]]; then
    python $IDF_PATH/components/esptool_py/esptool/esptool.py --chip esp8266 --port /dev/ttyUSB0 --baud 115200 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size 2MB 0x0 $1/build/bootloader/bootloader.bin 0x10000 $1/build/ledc.bin 0x8000 $1/build/partitions_singleapp.bin
elif [[ $1 == *"./projects/peripherals/hw_timer"* ]]; then
    python $IDF_PATH/components/esptool_py/esptool/esptool.py --chip esp8266 --port /dev/ttyUSB0 --baud 115200 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size 2MB 0x0 $1/build/bootloader/bootloader.bin 0x10000 $1/build/hw_timer.bin 0x8000 $1/build/partitions_singleapp.bin
elif [[ $1 == *"./projects/peripherals/uart_events"* ]]; then
    python $IDF_PATH/components/esptool_py/esptool/esptool.py --chip esp8266 --port /dev/ttyUSB0 --baud 115200 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size 2MB 0x0 $1/build/bootloader/bootloader.bin 0x10000 $1/build/uart_events.bin 0x8000 $1/build/partitions_singleapp.bin
elif [[ $1 == *"./projects/peripherals/uart_echo"* ]]; then
    python $IDF_PATH/components/esptool_py/esptool/esptool.py --chip esp8266 --port /dev/ttyUSB0 --baud 115200 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size 2MB 0x0 $1/build/bootloader/bootloader.bin 0x10000 $1/build/uart_echo.bin 0x8000 $1/build/partitions_singleapp.bin
elif [[ $1 == *"./projects/peripherals/gpio"* ]]; then
    python $IDF_PATH/components/esptool_py/esptool/esptool.py --chip esp8266 --port /dev/ttyUSB0 --baud 115200 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size 2MB 0x0 $1/build/bootloader/bootloader.bin 0x10000 $1/build/gpio.bin 0x8000 $1/build/partitions_singleapp.bin
elif [[ $1 == *"./projects/peripherals/spi_oled"* ]]; then
    python $IDF_PATH/components/esptool_py/esptool/esptool.py --chip esp8266 --port /dev/ttyUSB0 --baud 115200 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size 2MB 0x0 $1/build/bootloader/bootloader.bin 0x10000 $1/build/spi_oled.bin 0x8000 $1/build/partitions_singleapp.bin
elif [[ $1 == *"./projects/peripherals/uart_select"* ]]; then
    python $IDF_PATH/components/esptool_py/esptool/esptool.py --chip esp8266 --port /dev/ttyUSB0 --baud 115200 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size 2MB 0x0 $1/build/bootloader/bootloader.bin 0x10000 $1/build/uart_select.bin 0x8000 $1/build/partitions_singleapp.bin
elif [[ $1 == *"./projects/peripherals/i2c"* ]]; then
    python $IDF_PATH/components/esptool_py/esptool/esptool.py --chip esp8266 --port /dev/ttyUSB0 --baud 115200 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size 2MB 0x0 $1/build/bootloader/bootloader.bin 0x10000 $1/build/i2c.bin 0x8000 $1/build/partitions_singleapp.bin
elif [[ $1 == *"./projects/get-started/hello_world"* ]]; then
    python $IDF_PATH/components/esptool_py/esptool/esptool.py --chip esp8266 --port /dev/ttyUSB0 --baud 115200 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size 2MB 0x0 $1/build/bootloader/bootloader.bin 0x10000 $1/build/hello-world.bin 0x8000 $1/build/partitions_singleapp.bin
elif [[ $1 == *"./projects/storage/spiffs"* ]]; then
    python $IDF_PATH/components/esptool_py/esptool/esptool.py --chip esp8266 --port /dev/ttyUSB0 --baud 115200 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size 2MB 0x0 $1/build/bootloader/bootloader.bin 0x10000 $1/build/spiffs.bin 0x8000 $1/build/partitions_example.bin
elif [[ $1 == *"./projects/provisioning/legacy/softap_prov"* ]]; then
    python $IDF_PATH/components/esptool_py/esptool/esptool.py --chip esp8266 --port /dev/ttyUSB0 --baud 115200 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size 2MB 0x0 $1/build/bootloader/bootloader.bin 0x10000 $1/build/softap_prov.bin 0x8000 $1/build/partitions_singleapp.bin
elif [[ $1 == *"./projects/provisioning/legacy/custom_config"* ]]; then
    python $IDF_PATH/components/esptool_py/esptool/esptool.py --chip esp8266 --port /dev/ttyUSB0 --baud 115200 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size 2MB 0x0 $1/build/bootloader/bootloader.bin 0x10000 $1/build/custom_config.bin 0x8000 $1/build/partitions_singleapp.bin
elif [[ $1 == *"./projects/wifi/getting_started/softAP"* ]]; then
    python $IDF_PATH/components/esptool_py/esptool/esptool.py --chip esp8266 --port /dev/ttyUSB0 --baud 115200 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size 2MB 0x0 $1/build/bootloader/bootloader.bin 0x10000 $1/build/wifi_softAP.bin 0x8000 $1/build/partitions_singleapp.bin
elif [[ $1 == *"./projects/wifi/getting_started/station"* ]]; then
    python $IDF_PATH/components/esptool_py/esptool/esptool.py --chip esp8266 --port /dev/ttyUSB0 --baud 115200 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size 2MB 0x0 $1/build/bootloader/bootloader.bin 0x10000 $1/build/wifi_station.bin 0x8000 $1/build/partitions_singleapp.bin
elif [[ $1 == *"./projects/wifi/smart_config"* ]]; then
    python $IDF_PATH/components/esptool_py/esptool/esptool.py --chip esp8266 --port /dev/ttyUSB0 --baud 115200 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size 2MB 0x0 $1/build/bootloader/bootloader.bin 0x10000 $1/build/smart_config.bin 0x8000 $1/build/partitions_singleapp.bin
elif [[ $1 == *"./projects/wifi/espnow"* ]]; then
    python $IDF_PATH/components/esptool_py/esptool/esptool.py --chip esp8266 --port /dev/ttyUSB0 --baud 115200 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size 2MB 0x0 $1/build/bootloader/bootloader.bin 0x10000 $1/build/espnow_example.bin 0x8000 $1/build/partitions_singleapp.bin
elif [[ $1 == *"./projects/wifi/sniffer"* ]]; then
    python $IDF_PATH/components/esptool_py/esptool/esptool.py --chip esp8266 --port /dev/ttyUSB0 --baud 115200 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size 2MB 0x0 $1/build/bootloader/bootloader.bin 0x10000 $1/build/sniffer.bin 0x8000 $1/build/partitions_singleapp.bin
elif [[ $1 == *"./projects/wifi/roaming"* ]]; then
    python $IDF_PATH/components/esptool_py/esptool/esptool.py --chip esp8266 --port /dev/ttyUSB0 --baud 115200 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size 2MB 0x0 $1/build/bootloader/bootloader.bin 0x10000 $1/build/roaminng.bin 0x8000 $1/build/partitions_singleapp.bin
elif [[ $1 == *"./projects/wifi/power_save"* ]]; then
    python $IDF_PATH/components/esptool_py/esptool/esptool.py --chip esp8266 --port /dev/ttyUSB0 --baud 115200 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size 2MB 0x0 $1/build/bootloader/bootloader.bin 0x10000 $1/build/power_save.bin 0x8000 $1/build/partitions_singleapp.bin
elif [[ $1 == *"./projects/wifi/wps"* ]]; then
    python $IDF_PATH/components/esptool_py/esptool/esptool.py --chip esp8266 --port /dev/ttyUSB0 --baud 115200 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size 2MB 0x0 $1/build/bootloader/bootloader.bin 0x10000 $1/build/wps_example.bin 0x8000 $1/build/partitions_singleapp.bin
elif [[ $1 == *"./projects/wifi/wpa2_enterprise"* ]]; then
    python $IDF_PATH/components/esptool_py/esptool/esptool.py --chip esp8266 --port /dev/ttyUSB0 --baud 115200 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size 2MB 0x0 $1/build/bootloader/bootloader.bin 0x10000 $1/build/wpa2-enterprise.bin 0x8000 $1/build/partitions_singleapp.bin
elif [[ $1 == *"./projects/wifi/iperf"* ]]; then
    python $IDF_PATH/components/esptool_py/esptool/esptool.py --chip esp8266 --port /dev/ttyUSB0 --baud 115200 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size 2MB 0x0 $1/build/bootloader/bootloader.bin 0x10000 $1/build/iperf.bin 0x8000 $1/build/partitions_singleapp.bin
else
    exit 1
fi

exit 0
