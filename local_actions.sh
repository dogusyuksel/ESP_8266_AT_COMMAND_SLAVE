#!/bin/bash

# important!! first call must have '-b' option
./docker_ctl.sh -b -s -c 'cd /workspace/tools && make'
./docker_ctl.sh -s -c 'cd /workspace && export IDF_PATH="/ESP8266_RTOS_SDK" && ./build_all.sh "./projects/protocols/sockets/tcp_server"'
