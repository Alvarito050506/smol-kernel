#include <kernel.h>
#include <string.h>

struct
{
	int width;
	int height;
	int bpp;
	int bpl;
	int rgb;
	unsigned char* buff[2];
} fb;

void fb_init()
{
	/* TODO: make this dynamic(-ish) */
	mbox[0] = 35 * 4; // Length of message in bytes
	mbox[1] = MBOX_REQUEST;

	mbox[2] = MBOX_TAG_SETPHYWH; // Tag identifier
	mbox[3] = 8; // Size in bytes
	mbox[4] = 8; // Bis
	mbox[5] = 1440; // Width
	mbox[6] = 900; // Height

	mbox[7] = MBOX_TAG_SETVIRTWH;
	mbox[8] = 8;
	mbox[9] = 8;
	mbox[10] = 1440;
	mbox[11] = 900;

	mbox[12] = MBOX_TAG_SETVIRTOFF;
	mbox[13] = 8;
	mbox[14] = 8;
	mbox[15] = 0; // X
	mbox[16] = 0; // Y

	mbox[17] = MBOX_TAG_SETDEPTH;
	mbox[18] = 4;
	mbox[19] = 4;
	mbox[20] = 32; // Bits per pixel

	mbox[21] = MBOX_TAG_SETPXLORDR;
	mbox[22] = 4;
	mbox[23] = 4;
	mbox[24] = 1; // RGB

	mbox[25] = MBOX_TAG_GETFB;
	mbox[26] = 8;
	mbox[27] = 8;
	mbox[28] = 4096;
	mbox[29] = 0;

	mbox[30] = MBOX_TAG_GETPITCH;
	mbox[31] = 4;
	mbox[32] = 4;
	mbox[33] = 0; // Bytes per line

	mbox[34] = MBOX_TAG_LAST;

	// Check call is successful and we have a pointer with depth 32
	if (mbox_call(MBOX_CH_PROP) && mbox[20] == 32 && mbox[28] != 0)
	{
		mbox[28] &= 0x3fffffff; // Convert GPU address to ARM address
		fb.width = mbox[10];
		fb.height = mbox[11];
		fb.bpl = mbox[33];
		fb.rgb = mbox[24];
		fb.bpp = 3;
		fb.buff[0] = (unsigned char*)((long)mbox[28]);
		fb.buff[1] = malloc(fb.width * fb.height * fb.bpp);
	}
}

void draw_pixel(uint32_t x, uint32_t y, uint32_t color)
{
	uint32_t off = (y * fb.bpl) + (x * 4);
	*((uint32_t*)(fb.buff[1] + off)) = color;
	return;
}

void fb_update()
{
	memcpy(fb.buff[0], fb.buff[1], fb.width * fb.height * fb.bpp);
	return;
}
