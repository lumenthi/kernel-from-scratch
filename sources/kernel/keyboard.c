#include "keyboard.h"
#include "kernel.h"

const char keyboard_mapping[256] =
{
	0, ESC,
	'1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=',
	BCKSPC, TAB,
	'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']',
	ENTER, LCTRL,
	'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',
	LSHIFT,
	'\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/',
	RSHIFT, '*', LALT, ' ', CAPSLOCK
};

char	oldc;

bool	is_print(char c)
{
	if (c > 0 && c < 127)
		return true;
	return false;
}

void	keyboard_handler()
{
	char c;
	c = inb(0x60);
	if (c > 0 && c < 256) {
		c = keyboard_mapping[c];
		if (c != oldc && is_print(c)) {
			kputchar(c);
			oldc = c;
		}
	}
}
