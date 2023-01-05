/* Inline: By declaring a function inline, you can direct GCC to make calls to
 * that function faster.
 * One way GCC can achieve this is to integrate that function's code into the
 * code for its callers.
 * If you declare small functions which are performed repeatedly, inline can make
 * a big performance difference but at the cost of code size */

/* Send values on a I/O location */

/* AT&T Syntax */

/* OUT transfers data from the register AL,AX,EAX to the output port
 * in the DX register
 * outb: the b means BYTE
 * NO OTHER REGISTERS CAN BE USED FOR THIS INSTRUCTION
*/

/* ": :" If there are no output operands but there are input operands,
 *	you must place two consecutive colons surrounding the place where the output
 *	operands would go
 *
 *	"%0, %1" %0 is the first argument (%al) and %1 the second (%dx)
 *
 *	x86 family machine constraints:
 *		"a" means i want my value (val) in the AX register (al/ax/eax)
 *		"N" allows immediate byte for ports from 0-255
 *		"d" means i want my value (in DX)
 *		"Nd" means that if the value fits 8 bits, you don't need extra instructions
 *			to move it in edx reg, its for optimization
*/

#include <stdint.h>

void		outb(uint16_t port, uint8_t val)
{
	asm volatile("outb %0, %1" : : "a"(val), "Nd"(port));
	/*							 : : only input */
}

void		outw(uint16_t port, uint16_t val)
{
	asm volatile("outw %0, %w1" : : "a"(val), "Nd" (port));
}
