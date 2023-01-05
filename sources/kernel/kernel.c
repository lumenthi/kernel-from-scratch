#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "kernel.h"
#include "kernlib.h"
#include "printk.h"
#include "keyboard.h"
#include "vga.h"

bool running;

void kernel_entry(void)
{
	running = true;
	/* Initialize terminal interface */
	terminal_initialize();

	unsigned char c;
	while (running) {
		c = keyboard_handler();
		switch (c) {
			case KP_ESC:
				running = false;
				break;
			case KR_ESC:
				running = false;
				break;
		}
	}
	/* Shutdown */
	poweroff();
	return;
}
