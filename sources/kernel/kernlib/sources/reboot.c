/*
	The original 8042 "PS/2 keyboard controller" design had some extra pins on the controller and the cheapskate IBM engineers did wire lots of stuff to these extra pins. One pin was wired to the CPU reset pin, another unused pin was used to fix the 80286 address wraparound incompatibility, the fix was called the the A20 gate.

	The command byte 0xFx means "pulse the chosen line down for 6 milliseconds", with E choosing the reset line (the bit 0 is zeroed). The effect is resetting the CPU so that it starts executing code according to its boot sequence.
*/

#include "kernlib.h"

/* Keyboard IO Ports */
#define KBRD_CMDPORT 0x64
#define KBRD_DATAPORT 0x60

/* keyboard interface bits */
#define KBRD_BIT_KDATA 0 /* keyboard data is in buffer (output buffer is empty) (bit 0) */
#define KBRD_BIT_UDATA 1 /* user data is in buffer (command buffer is empty) (bit 1) */

#define KBRD_RESET 0xFE /* reset CPU command */

#define bit(n) (1<<(n)) /* Set bit n to 1 */

/* Check if bit n in flags is set */
#define check_flag(flags, n) ((flags) & bit(n))

void reboot(void)
{
	uint8_t temp;

	asm volatile ("cli"); /* disable all interrupts */

	/* Clear all keyboard buffers (output and command buffers) */
	do
	{
		temp = inb(KBRD_CMDPORT); /* empty user data */
		if (check_flag(temp, KBRD_BIT_KDATA) != 0)
			inb(KBRD_DATAPORT); /* empty keyboard data */
	} while (check_flag(temp, KBRD_BIT_UDATA) != 0);

	outb(KBRD_CMDPORT, KBRD_RESET); /* pulse CPU reset line */
}
