#include "kernlib.h"
#include "vga.h"
#include "printk.h"

void	newline()
{
	terminal_column = 0;
	terminal_row++;
	if (terminal_row == VGA_HEIGHT) {
		terminal_shift_up();
		terminal_row = VGA_HEIGHT - 1;
		printk("%s", KPROMPT);
	}
	if (terminal_show_cursor)
		update_cursor();
}

void kputchar(char c) 
{
	if (c == '\n') {
		newline();
		return ;
	}
	if (terminal_column == VGA_WIDTH) {
		terminal_column = 0;
		terminal_row++;
		if (terminal_row == VGA_HEIGHT) {
			terminal_shift_up();
			terminal_row = VGA_HEIGHT - 1;
		}
	}
	terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
	terminal_column++;
	if (terminal_show_cursor)
		update_cursor();
}
