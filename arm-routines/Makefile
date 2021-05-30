SRC:=$(wildcard src/*.S)
OBJS:=$(SRC:src/%.S=../build/%.o)

include ../config.mk

all: $(OBJS)

../build/%.o: ./src/%.S
	$(CC) $(CFLAGS) -c $< -o $@
