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
	unsigned char c;

	running = true;
	c = keyboard_handler(); // Flush the keyboard
	/* Initialize terminal interface */
	terminal_initialize();

	/* GDT */
	init_gdt();
	/* TODO: load_gdt();*/

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
	poweroff();
	return;
}
