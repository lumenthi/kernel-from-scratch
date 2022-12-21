#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "kernel.h"
#include "kernlib.h"
#include "printk.h"
#include "keyboard.h"
#include "vga.h"

void kernel_entry(void) 
{
	/* Initialize terminal interface */
	terminal_initialize();

	unsigned char c;
	while (1) {
		c = keyboard_handler();
		switch (c) {
			case KP_ESC:
				break;
		}
	}
}
