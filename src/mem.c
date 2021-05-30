#include <kernel.h>
#include <stddef.h>
#include <stdint.h>

static volatile uint32_t io_base;
//static volatile uint32_t max_mem;
extern uint8_t __end;

void mem_write(uint32_t addr, uint32_t val)
{
	*(volatile uint32_t*)(io_base + addr) = val;
	return;
}

uint32_t mem_read(uint32_t addr)
{
	return *(volatile uint32_t*)(io_base + addr);
}

void mem_init()
{
	register uint32_t r;

	__asm__ volatile ("mrs %0, midr_el1" : "=r"(r));
	switch ((r >> 4) & 0xfff)
	{
		case 0xd03:
			io_base = 0x3f000000;
		break;
		case 0xd08:
			io_base = 0xfe000000;
		break;
		default:
			panic();
	}
	return;
}

/* TODO: This is basically sbrk */
void* malloc(int sz)
{
	static uint8_t* heap_end;
	uint8_t* prev_heap_end;

	if (heap_end == NULL)
	{
		heap_end = (uint8_t*)((uint32_t)&__end + 512);
	}

	prev_heap_end = heap_end;
	if (heap_end + sz > io_base - 1)
	{
		return NULL;
	}
	heap_end += sz;
	return (void*)prev_heap_end;
}
