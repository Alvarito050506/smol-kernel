#include <kernel.h>

void main()
{
	int x = 0;
	int y = 0;
	int w = 0;
	int h = 0;

	mem_init();
	fb_init();
	rand_init();

	w = rand() % 1440;
	h = rand() % 900;

	while (x < w)
	{
		y = 0;
		while (y < h)
		{
			draw_pixel(x, y, 0xff00ff);
			y++;
		}
		x++;
	}
	fb_update();

	usleep(1000);
	return;
}
