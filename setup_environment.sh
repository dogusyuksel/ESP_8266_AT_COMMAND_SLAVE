#!/bin/bash

update_repo () {
   cd $1
   git clean -fd
   git checkout *
   git pull
   cd -
}

if [ ! -d "docker" ]; then
    git clone https://github.com/dogusyuksel/embedded_docker.git docker
else
    update_repo "docker"
fi

if [ ! -d "cjson" ]; then
    git clone https://github.com/DaveGamble/cJSON.git cjson
    cd cjson
    git checkout 87d8f0961a01bf09bef98ff89bae9fdec42181ee
    mkdir build
    cd build
    cmake ..
    make
    cd -
fi

exit 0
