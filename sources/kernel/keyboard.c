#include "keyboard.h"
#include "kernel.h"
#include "printk.h"

const unsigned char keyboard_mapping[256] =
{
	0, 0,
	'1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=',
	'\b', '\t',
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

unsigned char	keyboard_handler()
{
	c = inb(0x60);
	if (c == oldc)
		return c;
	//printk("0x%x ", c);
	if (oldc == KEXTENDED) {
		/* TODO: handle line too big */
		if (c == KR_RIGHT && get_terminal_char(terminal_column, terminal_row) != 0) {
			terminal_column++;
			update_cursor();
		}
		else if (c == KR_LEFT && terminal_column > KPROMPT_SIZE) {
			terminal_column--;
			update_cursor();
		}
	}
	oldc = c;
	c = keyboard_mapping[c];
	if (is_print(c)) {
		if (get_terminal_char(terminal_column, terminal_row) == 0)
			kputchar(c);
		else {
			terminal_shift_right();
			kputchar(c);
		}
	}
	return c;
}
