#ifndef KEYBOARD_H
#define KEYBOARD_H

/*
 * A keyboard has three 8-bit registers for communication with CPU:
 *	input buffer: Can be written by the CPU by writing port 0x60 or port 0x64
 *	output buffer: Can be read by the CPU by reading port 0x60
 *	status register: Can be read by the CPU by reading port 0x64
 *
 * If the CPU writes to port 0x64, the byte is interpreted as a command byte
 * If the CPY writes to port 0x60, the byte is interpreted as a data byte
*/

/* IO Ports */
#define DATA_PORT		0x60
#define COMMAND_PORT	0x64

/* Keyboard special keys */
#define ESC			0x01
#define BCKSPC		0x0E
#define TAB			0x0F
#define ENTER		0x1C
#define LCTRL		0x1D
#define LSHIFT		0x2A
#define RSHIFT		0x36
#define LALT		0x38
#define CAPSLOCK	0x3A

void	keyboard_handler(void);

#endif
