#include "kernlib.h"
#include "vga.h"

void kputchar(char c) 
{
	if (c == '\n') {
		terminal_column = 0;
		terminal_row++;
		return ;
	}
	terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
	if (++terminal_column == VGA_WIDTH) {
		terminal_column = 0;
		if (++terminal_row == VGA_HEIGHT)
			terminal_row = 0;
	}
	if (terminal_show_cursor)
		update_cursor(terminal_column, terminal_row);
}
