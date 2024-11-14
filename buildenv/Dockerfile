FROM ubuntu:20.04
#FROM ethanmilon/gcc-cross-i386-elf

# Install glibc and other tools on the host system
RUN apt-get update && \
    apt-get install -y \
    libc6-dev \
    build-essential \
    nasm \
    xorriso \
    grub-pc-bin \
    grub-common \
    gcc-multilib \
    vim-common \
    sqlite3 \
    libsqlite3-dev \
    xxd \
    genisoimage \
    lua5.2 \
    musl-tools \
    mtools \
    curl \
    wget \
    git \
    bison \
    flex \
    libgmp3-dev \
    libmpfr-dev \
    libmpc-dev \
    texinfo \
    sudo \
    dosfstools \
    gcc-i686-linux-gnu \
    binutils-i686-linux-gnu \
    xz-utils

ENV PATH="/sbin:${PATH}"

VOLUME /root/env
WORKDIR /root/env
