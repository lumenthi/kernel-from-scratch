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
	line_count = 0;
	if (current_cursor->y == VGA_HEIGHT) {
		terminal_shift_up();
		current_cursor->y = VGA_HEIGHT - 1;
		printk("%s", KPROMPT);
	}
	if (terminal_show_cursor)
		update_cursor();
}

void	kputchar(char c) 
{
	if (c == '\n') {
		newline();
		return ;
	}
	else if (c == '\e') {
		ansi = true;
		ansi_index = 0;
		for (int i = 0; i < 5; i++)
			ansi_sequ[i] = '|';
		return ;
	}
	if (ansi == true) {
		ansi_sequ[ansi_index++] = c;
		if (c == 'm' || ansi_index >= 4) {
			ansi_sequ[ansi_index] = 0;
			analyze_ansi(ansi_sequ);
			ansi = false;
		}
		return ;
	}
	if (current_cursor->x == VGA_WIDTH) {
		current_cursor->x = 0;
		current_cursor->y++;
		line_count++;
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
