#include <kernel.h>
#include <stdint.h>

void rand_init()
{
	mem_write(RNG_STATUS, 0x40000);
	mem_write(RNG_INT_MASK, mem_read(RNG_INT_MASK) | 1);
	mem_write(RNG_CTRL, mem_read(RNG_CTRL) | 1);
	return;
}

uint64_t rand()
{
	uint64_t n = 0;

	SLEEP_WHILE(!(mem_read(RNG_STATUS) >> 24));
	n = mem_read(RNG_DATA) & 0xffffffff;
	SLEEP_WHILE(!(mem_read(RNG_STATUS) >> 24));
	n |= (uint64_t)(mem_read(RNG_DATA)) << 32;
	return n;
}

void usleep(uint32_t usec)
{
	register uint32_t f, t, r;

	// Get the current counter frequency
	__asm__ volatile ("mrs %0, cntfrq_el0" : "=r"(f));
	// Read the current counter
	__asm__ volatile ("mrs %0, cntpct_el0" : "=r"(t));
	// Calculate expire value for counter
	t += ((f / 1000) * usec) / 1000;
	do
	{
		__asm__ volatile ("mrs %0, cntpct_el0" : "=r"(r));
	} while (r < t);
	return;
}

void csleep(uint32_t cl)
{
	while (cl--)
	{
		__asm__ volatile ("nop");
	}
	return;
}

void panic()
{
	while (1) {}
}
