#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "kernel.h"
#include "kernlib.h"
#include "printk.h"
#include "keyboard.h"
#include "vga.h"
#include "shell.h"

bool running;

void kernel_entry(void)
{
	running = true;
	/* Initialize terminal interface */
	terminal_initialize();
	shell_initialize();

	unsigned char c;

	while (running) {
		c = keyboard_handler();
		switch (c) {
			case KP_ENTER:
				get_command();
				printk("Command to execute: [%s]", shell_buf);
				// kputchar('\n');
				shell_reset();
				break;
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
