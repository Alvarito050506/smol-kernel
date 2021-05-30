# Copy this file to config.mk and edit as needed
PREFIX:=aarch64-none-elf-

CC:=$(PREFIX)gcc
LD:=$(PREFIX)ld
OBJCOPY:=$(PREFIX)objcopy
AR:=$(PREFIX)ar

NOSTD:=-nostdinc -nostdlib -nostartfiles
CFLAGS:=-Wall -O3 -ffreestanding $(NOSTD) -I./include/
