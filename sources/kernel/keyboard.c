#include "keyboard.h"
#include "kernel.h"
#include "printk.h"
#include "vga.h"

const unsigned char keyboard_mapping[256] =
{
	0, 0,
	'1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=',
	0, '\t',
	'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']',
	'\n', 0,
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

size_t	delay;
unsigned char	c;
unsigned char	oldc;

bool	shift = false;
bool	repeat = false;

unsigned char	keyboard_handler()
{
	while ((c = inb(0x60)) == oldc && !repeat);
	if (oldc == KEXTENDED) {
		if (c == KR_RIGHT &&
			get_terminal_char(current_cursor->x, current_cursor->y) != 0) {
			current_cursor->x++;
			update_cursor();
		}
		else if (c == KR_LEFT &&
		(current_cursor->x > KPROMPT_SIZE ||
			(line_count > 0 && current_cursor->y > VGA_HEIGHT - line_count))) {
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
		oldc = c;
		return keyboard_mapping[c];
	}
	else if (c == KP_BACKSPACE) {
		if (current_cursor->x > KPROMPT_SIZE || line_count > 0) {
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
		oldc = c;
		return keyboard_mapping[c];
	}
	oldc = c;
	c = keyboard_mapping[c];
	// printk("Special keyboard\n");
	if (is_print(c)) {
		if (get_terminal_char(current_cursor->x, current_cursor->y) == 0) {
			kputchar(c);
		}
		else {
			terminal_shift_right();
			kputchar(c);
		}
	}
	return oldc;
}
