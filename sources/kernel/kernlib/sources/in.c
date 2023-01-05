/* INx receives a value from an I/O location
 * ex: in $0x60, %al, get the scancode ID of the last character type on the keyboard to al */

/* = means assign EAX value to ret */

#include <stdint.h>

uint8_t	inb(uint16_t port)
{
	uint8_t ret;
	asm volatile ( "inb %1, %0" : "=a"(ret) : "Nd"(port) );
	/*							: output    : input */
	return ret;
}
