#!/bin/bash

# Update the package list
sudo apt-get update

# Install the specified packages
sudo apt-get install -y \
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
    xz-utils
