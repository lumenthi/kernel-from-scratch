#include "keyboard.h"
#include "kernel.h"
#include "printk.h"
#include "vga.h"
#include "shell.h"

const unsigned char keyboard_mapping[256] =
{
	0, 0,
	'1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=',
	0, '\t',
	'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']',
	0, 0,
	'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',
	0,
	'\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/',
	0, '*', 0, ' ', 0
};

bool	is_print(char c)
{
	if (c > 0 && c < 127)
		return true;
	return false;
}

size_t			delay;
unsigned char	c;
unsigned char	oldc;

bool	shift = false;
bool	repeat = false;
bool	kcaps = false;
bool	kshift = false;

unsigned char	keyboard_handler()
{
	while ((c = inb(0x60)) == oldc && !repeat);
	if (c == oldc)
		return c;
	if (oldc == KEXTENDED) {
		oldc = c;
		if (c == KP_RIGHT &&
			get_char_at(current_cursor->x, current_cursor->y) != 0) {
			current_cursor->x++;
			update_cursor();
		}
		else if (c == KP_LEFT &&
		(current_cursor->x > KPROMPT_SIZE ||
			(line_count > 0 && current_cursor->y > VGA_HEIGHT - line_count - 1))) {
			if (current_cursor->x <= 0) {
				current_cursor->x = VGA_WIDTH;
				current_cursor->y--;
			}
			else
				current_cursor->x--;
			update_cursor();
		}
		else if (c == KR_PAGEUP || c == KR_PAGEDOWN)
			swap_screen();
		else if (c == KR_DELETE) {
			kputchar(' ');
			current_cursor->x--;
			terminal_shift_left();
			update_cursor();
		}
		else if (c == KR_HOME) {
			current_cursor->x = KPROMPT_SIZE;
			current_cursor->y = VGA_HEIGHT - line_count - 1;
			update_cursor();
			return 0;
		}
		else if (c == KR_END) {
			size_t index = current_cursor->x + current_cursor->y * VGA_WIDTH;
			while (get_char_at_index(index) != 0) {
				current_cursor->x++;
				index++;
			}
			update_cursor();
		}
		return keyboard_mapping[c];
	}
	oldc = c;
	if (c == KP_BACKSPACE) {
		if (current_cursor->x > KPROMPT_SIZE ||
			(line_count > 0 && current_cursor->y > VGA_HEIGHT - line_count - 1)) {
			current_cursor->x--;
			kputchar(0);
			current_cursor->x--;
			terminal_shift_left();
			if (current_cursor->x <= 0) {
				line_count--;
				current_cursor->y--;
				current_cursor->x = VGA_WIDTH;
			}
			update_cursor();
		}
		return keyboard_mapping[c];
	}
	else if (c == KP_LSHIFT || c == KP_RSHIFT)
		kshift = true;
	else if (c == KR_LSHIFT || c == KR_RSHIFT)
		kshift = false;
	else if (c == KR_CAPSLOCK)
		kcaps = kcaps == 1 ? 0 : 1;
	else if (c == KP_ENTER) {
		get_command();
		if (shell_buf && strlen(shell_buf)) {
			newline();
			handle_command(shell_buf);
		}
		else {
			current_cursor->x = VGA_WIDTH - 1;
			current_cursor->y = VGA_HEIGHT - 1;
			newline();
		}
		printk("%s", KPROMPT);
		return c;
	}
	c = keyboard_mapping[c];
	if (is_print(c)) {
		if (kcaps ^ kshift)
			c = toupper(c);
		if (get_char_at(current_cursor->x, current_cursor->y) == 0) {
			kputchar(c);
		}
		else {
			terminal_shift_right();
			kputchar(c);
		}
	}
	return oldc;
}
