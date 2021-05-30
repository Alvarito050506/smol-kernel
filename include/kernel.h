#ifndef KERNEL_H
#define KERNEL_H
#include <stdint.h>

#define MEM_PTR(addr) (*((volatile unsigned int*)(io_base + addr)))
#define SLEEP_WHILE(cond) while (cond) {}
#define MBOX_REQUEST 0
#define MBOX_FULL 0x80000000
#define MBOX_EMPTY 0x40000000
#define MBOX_RESPONSE 0x80000000
#define PM_WDOG_MAGIC 0x5a000000
#define PM_RSTC_FULLRST 0x00000020

enum
{
	MBOX_CH_POWER = 0,
	MBOX_CH_FB = 1,
	MBOX_CH_VUART = 2,
	MBOX_CH_VCHIQ = 3,
	MBOX_CH_LEDS = 4,
	MBOX_CH_BTNS = 5,
	MBOX_CH_TOUCH = 6,
	MBOX_CH_COUNT = 7,
	MBOX_CH_PROP = 8 // Request from ARM for response by VideoCore
};

enum
{
	MBOX_BASE = 0xb880,
	MBOX_READ = MBOX_BASE,
	MBOX_POLL = MBOX_BASE + 0x10,
	MBOX_SENDER = MBOX_BASE + 0x14,
	MBOX_STATUS = MBOX_BASE + 0x18,
	MBOX_CONFIG = MBOX_BASE + 0x1c,
	MBOX_WRITE = MBOX_BASE + 0x20,
	RNG_CTRL = 0x00104000,
	RNG_STATUS = 0x00104004,
	RNG_DATA = 0x00104008,
	RNG_INT_MASK = 0x00104010,
	PM_RSTC = 0x0010001c,
	PM_RSTS = 0x00100020,
	PM_WDOG = 0x00100024,
	GPFSEL0 = 0x00200000,
	GPFSEL1 = 0x00200004,
	GPFSEL2 = 0x00200008,
	GPFSEL3 = 0x0020000c,
	GPFSEL4 = 0x00200010,
	GPFSEL5 = 0x00200014,
	GPSET0 = 0x0020001c,
	GPSET1 = 0x00200020,
	GPCLR0 = 0x00200028,
	GPLEV0 = 0x00200034,
	GPLEV1 = 0x00200038,
	GPEDS0 = 0x00200040,
	GPEDS1 = 0x00200044,
	GPHEN0 = 0x00200064,
	GPHEN1 = 0x00200068,
	GPPUD = 0x00200094,
	GPPUDCLK0 = 0x00200098,
	GPPUDCLK1 = 0x0020009c
};

enum
{
	MBOX_TAG_SETPOWER = 0x28001,
	MBOX_TAG_SETCLKRATE = 0x38002,
	MBOX_TAG_SETPHYWH = 0x48003,
	MBOX_TAG_SETVIRTWH = 0x48004,
	MBOX_TAG_SETVIRTOFF = 0x48009,
	MBOX_TAG_SETDEPTH = 0x48005,
	MBOX_TAG_SETPXLORDR = 0x48006,
	MBOX_TAG_GETFB = 0x40001,
	MBOX_TAG_GETPITCH = 0x40008,
	MBOX_TAG_LAST = 0
};

extern volatile uint32_t mbox[36];

void mem_write(uint32_t addr, uint32_t val);
uint32_t mem_read(uint32_t addr);
void mem_init();
void* malloc(int sz);

uint32_t mbox_call(uint8_t channel);

void fb_init();
void draw_pixel(uint32_t x, uint32_t y, uint32_t color);
void fb_update();

void rand_init();
uint64_t rand();
void usleep(uint32_t usec);
void csleep(uint32_t cl);
void panic();

void shutdown();
void reset();

#endif /* KERNEL_H */
