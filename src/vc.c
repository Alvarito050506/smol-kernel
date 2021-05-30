#include <kernel.h>
#include <stdint.h>

/*
 * The buffer must be 16-byte aligned as only the upper 28 bits of the
 * address can be passed via the mailbox
 */
volatile uint32_t __attribute__((aligned(16))) mbox[36];

uint32_t mbox_call(uint8_t channel)
{
	// 28-bit address (MSB) and 4-bit value (LSB)
	uint32_t r = ((uint32_t)((int64_t)&mbox) &~ 0x0f) | (channel & 0x0f);

	// Wait until we can write
	SLEEP_WHILE(mem_read(MBOX_STATUS) & MBOX_FULL);

	// Write the address of our buffer to the mailbox with the channel appended
	mem_write(MBOX_WRITE, r);

	while (1)
	{
		// Wait until there's a reply
		SLEEP_WHILE(mem_read(MBOX_STATUS) & MBOX_EMPTY) {}

		if (mem_read(MBOX_READ) == r)
		{
			return mbox[1] == MBOX_RESPONSE;
		}
	}
	return 0;
}
