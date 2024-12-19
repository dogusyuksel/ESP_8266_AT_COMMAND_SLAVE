FROM ubuntu:22.04
ARG DEBIAN_FRONTEND=noninteractive

USER root

RUN apt-get update && \
    apt-get -y upgrade && \
    apt-get -y --no-install-recommends install \
        build-essential \
        git \
        git-core \
        git-lfs \
        python3-dbg \
        python3-dev \
        python3-pip \
        python3-pexpect \
        python3-git \
        python3-jinja2 \
        python3-subunit \
        vim \
        cmake \
        gcc-multilib \
        g++-multilib \
        software-properties-common \
        language-pack-en-base \
        wget \
        libncurses-dev \
        flex \
        bison \
        gperf \
        unzip && \
    apt-get -y clean

RUN git config --global --add safe.directory /workspace

RUN python3 -m pip install pyserial
RUN pip install pyparsing==2.4.2

RUN ln -s /usr/bin/python3 /usr/bin/python

RUN cd / && \
    mkdir esp && \
    cd esp && \
    wget https://dl.espressif.com/dl/xtensa-lx106-elf-gcc8_4_0-esp-2020r3-linux-amd64.tar.gz && \
    tar -xzf xtensa-lx106-elf-gcc8_4_0-esp-2020r3-linux-amd64.tar.gz
ENV PATH="/esp/xtensa-lx106-elf/bin:${PATH}"
RUN cd / && \
    git clone --recursive https://github.com/espressif/ESP8266_RTOS_SDK.git ESP8266_RTOS_SDK && \
    python3 -m pip install --user -r ESP8266_RTOS_SDK/requirements.txt

RUN cd / && mkdir thirdparty && \
    cd /thirdparty/ && git clone https://github.com/DaveGamble/cJSON.git cjson && \
    cd /thirdparty/cjson && git checkout 87d8f0961a01bf09bef98ff89bae9fdec42181ee && \
    mkdir build && cd build && cmake .. && make

CMD ["/bin/bash"]

WORKDIR /workspace/
