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

	/* Newline support is left as an exercise. */
	printk("Hello, kernel World!\nC'est moi KFS\n");

	printk("Coucou %d test de printk %x\n", -34, 0x60);
	while (1) {
		keyboard_handler();
	}
}
