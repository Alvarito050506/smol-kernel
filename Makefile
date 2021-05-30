SRC:=$(wildcard src/*.c)
STR_SRC:=$(wildcard arm-routines/src/*.S)
OBJS:=$(SRC:src/%.c=build/%.o)
STR_OBJS:=$(STR_SRC:arm-routines/src/%.S=build/%.o)

include config.mk

all: clean $(OBJS) str
	$(CC) $(CFLAGS) -c ./src/boot.S -o ./build/boot.o
	$(LD) $(NOSTD) ./build/boot.o $(OBJS) $(STR_OBJS) -T link.ld -o ./build/kernel8.elf
	$(OBJCOPY) -O binary ./build/kernel8.elf ./build/kernel8.img

build/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

test:
	qemu-system-aarch64 -M raspi3 -kernel ./build/kernel8.img -serial stdio -d int

str:
	$(MAKE) -C arm-routines

clean:
	rm -rf ./build/*
