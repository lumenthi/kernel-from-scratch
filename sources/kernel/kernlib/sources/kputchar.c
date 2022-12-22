#include "kernlib.h"
#include "vga.h"
#include "printk.h"

bool	ansi = false;
char	ansi_sequ[5];
int		ansi_index;

void	newline()
{
	current_cursor->x = 0;
	current_cursor->y++;
	if (current_cursor->y == VGA_HEIGHT) {
		terminal_shift_up();
		current_cursor->y = VGA_HEIGHT - 1;
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
	/* TODO: handle ansi when mutli screen is done */
	else if (c == '\e') {
		ansi = true;
		ansi_index = 0;
		return ;
	}
	if (ansi == true) {
		ansi_sequ[ansi_index] = (uint8_t)(terminal_buffer[current_cursor->y * VGA_WIDTH + current_cursor->x]);
		ansi_sequ[4] = 0;
		if (c == 'm') {
			for (int i = 0; i <= ansi_index; i++)
				terminal_putentryat(ansi_sequ[i], terminal_color, current_cursor->x++,
				current_cursor->y);
			//kputstr("ansi seq = |");
			//ansi_sequ);
			ansi = false;
		}
		return ;
	}
	if (current_cursor->x == VGA_WIDTH) {
		current_cursor->x = 0;
		current_cursor->y++;
		if (current_cursor->y == VGA_HEIGHT) {
			terminal_shift_up();
			current_cursor->y = VGA_HEIGHT - 1;
		}
	}
	terminal_putentryat(c, terminal_color, current_cursor->x, current_cursor->y);
	current_cursor->x++;
	if (terminal_show_cursor)
		update_cursor();
}
