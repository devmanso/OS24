## Architecture

- doc : Documentation
- src/stage1 : First bootloader chunk (full Asm)
- src/stage2 : Second bootloader chunk
- src/kernel : Core chunk
- src/lib : Libc and libk

## Depedencies

- gcc cross compiler (for i386)
- nasm
- mtools (add /sbin to your path, for fs)
- qemu-system-i386 or qemu-system-x86
- objcopy
- gdb
- xterm

# Building on Windows

1. docker build buildenv -t os-buildenv

2. docker run --privileged --cap-add=SYS_ADMIN --rm -it -v ${PWD}:/root/env os-buildenv
