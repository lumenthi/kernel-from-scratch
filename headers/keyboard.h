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

/*-----	Scancodes 1 -----*/
#define KEXTENDED			0xE0
/* Key Presses (KP) */
#define KP_ESC				0x01
#define KP_1				0x02
#define KP_2				0x03
#define KP_3				0x04
#define KP_4				0x05
#define KP_5				0x06
#define KP_6				0x07
#define KP_7				0x08
#define KP_8				0x09
#define KP_9				0x0A
#define KP_0				0x0B
#define KP_MINUS			0x0C
#define KP_EQUALS			0x0D
#define KP_BACKSPACE		0x0E

#define KP_TAB				0x0F
#define KP_Q				0x10
#define KP_W				0x11
#define KP_E				0x12
#define KP_R				0x13
#define KP_T				0x14
#define KP_Y				0x15
#define KP_U				0x16
#define KP_I				0x17
#define KP_O				0x18
#define KP_P				0x19
#define KP_OBRACKET			0x1A
#define KP_CBRACKET			0x1B
#define KP_ENTER			0x1C

#define KP_LCTRL			0x1D

#define KP_A				0x1E
#define KP_S				0x1F
#define KP_D				0x20
#define KP_F				0x21
#define KP_G				0x22
#define KP_H				0x23
#define KP_J				0x24
#define KP_K				0x25
#define KP_L				0x26
#define KP_SEMICOLON		0x27
#define KP_QUOTE			0x28

#define KP_BACKTICK			0x29

#define KP_LSHIFT			0x2A
#define KP_BACKQUOTE		0x2B
#define KP_Z				0x2C
#define KP_X				0x2D
#define KP_C				0x2E
#define KP_V				0x2F
#define KP_B				0x30
#define KP_N				0x31
#define KP_M				0x32
#define KP_COMMA			0x33
#define KP_DOT				0x34
#define KP_SLASH			0x35
#define KP_RSHIFT			0x36

#define KP_KPSTAR			0x37

#define KP_LALT				0x38
#define KP_SPACE			0x39

#define KP_CAPSLOCK			0x3A

#define KP_F1				0x3B
#define KP_F2				0x3C
#define KP_F3				0x3D
#define KP_F4				0x3E
#define KP_F5				0x3F
#define KP_F6				0x40
#define KP_F7				0x41
#define KP_F8				0x42
#define KP_F9				0x43
#define KP_F10				0x44

#define KP_NUMLOCK			0x45

#define KP_SCROLLLOCK		0x46

#define KP_KP7				0x47
#define KP_KP8				0x48
#define KP_KP9				0x49
#define KP_KPMINUS			0x4A

#define KP_KP4				0x4B
#define KP_KP5				0x4C
#define KP_KP6				0x4D
#define KP_KPPLUS			0x4E

#define KP_KP1				0x4F
#define KP_KP2				0x50
#define KP_KP3				0x51
#define KP_KP0				0x52
#define KP_KPDOT			0x53

#define KP_F11				0x57
#define KP_F12				0x58

/* Key Releases (KR) */
#define KR_ESC				0x81
#define KR_1				0x82
#define KR_2				0x83
#define KR_3				0x84
#define KR_4				0x85
#define KR_5				0x86
#define KR_6				0x87
#define KR_7				0x88
#define KR_8				0x89
#define KR_9				0x8A
#define KR_0				0x8B
#define KR_MINUS			0x8C
#define KR_EQUALS			0x8D
#define KR_BACKSPACE		0x8E

#define KR_TAB				0x8F
#define KR_Q				0x90
#define KR_W				0x91
#define KR_E				0x92
#define KR_R				0x93
#define KR_T				0x94
#define KR_Y				0x95
#define KR_U				0x96
#define KR_I				0x97
#define KR_O				0x98
#define KR_P				0x99
#define KR_OBRACKET			0x9A
#define KR_CBRACKET			0x9B
#define KR_ENTER			0x9C

#define KR_LCTRL			0x9D

#define KR_A				0x9E
#define KR_S				0x9F
#define KR_D				0xA0
#define KR_F				0xA1
#define KR_G				0xA2
#define KR_H				0xA3
#define KR_J				0xA4
#define KR_K				0xA5
#define KR_L				0xA6
#define KR_SEMICOLON		0xA7
#define KR_QUOTE			0xA8

#define KR_BACKTICK			0x29

#define KR_LSHIFT			0xAA
#define KR_BACKQUOTE		0xAB
#define KR_Z				0xAC
#define KR_X				0xAD
#define KR_C				0xAE
#define KR_V				0xAF
#define KR_B				0xB0
#define KR_N				0xB1
#define KR_M				0xB2
#define KR_COMMA			0xB3
#define KR_DOT				0xB4
#define KR_SLASH			0xB5
#define KR_RSHIFT			0xB6

#define KR_KPSTAR			0xB7

#define KR_LALT				0xB8
#define KR_SPACE			0xB9

#define KR_CAPSLOCK			0xBA

#define KR_F1				0xBB
#define KR_F2				0xBC
#define KR_F3				0xBD
#define KR_F4				0xBE
#define KR_F5				0xBF
#define KR_F6				0xC0
#define KR_F7				0xC1
#define KR_F8				0xC2
#define KR_F9				0xC3
#define KR_F10				0xC4

#define KR_NUMLOCK			0xC5

#define KR_SCROLLLOCK		0xC6

#define KR_KP7				0xC7
#define KR_KP8				0xC8
#define KR_KP9				0xC9
#define KR_KPMINUS			0xCA

#define KR_KP4				0xCB
#define KR_KP5				0xCC
#define KR_KP6				0xCD
#define KR_KPPLUS			0xCE

#define KR_KP1				0xCF
#define KR_KP2				0xD0
#define KR_KP3				0xD1
#define KR_KP0				0xD2
#define KR_KPDOT			0xD3

#define KR_F11				0xD7
#define KR_F12				0xD8

#define KP_RIGHT			0x4D
#define KP_UP				0x48
#define KP_LEFT				0x4B
#define KP_DOWN				0x50

#define KR_RIGHT			0xCD
#define KR_UP				0xC8
#define KR_LEFT				0xCB
#define KR_DOWN				0xD0

unsigned char	keyboard_handler(void);

#endif
