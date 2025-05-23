#!/usr/bin/env bash

set -e

gcc -g -m32 -fno-stack-protector -fno-builtin -c src/kernel/kernel.c -o build/kernel.o
gcc -g -m32 -fno-stack-protector -fno-builtin -c src/kernel/vga/vga.c -o build/vga.o
gcc -g -m32 -fno-stack-protector -fno-builtin -c src/kernel/gdt/gdt.c -o build/gdt.o

nasm -f elf32 src/bootloader/boot.asm -o build/boot.o
nasm -f elf32 src/kernel/gdt/gdt.asm -o build/gdts.o

ld -m elf_i386 -T src/linker.ld -o build/kernel build/boot.o build/kernel.o build/vga.o build/gdt.o build/gdts.o
