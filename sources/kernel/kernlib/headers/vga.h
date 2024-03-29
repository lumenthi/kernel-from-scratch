#ifndef VGA_H
#define VGA_H

#include <stddef.h>

enum vga_color {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};

#define VGA_WIDTH	80
#define VGA_HEIGHT	25

#define NB_SCREENS	2
#define SCREEN1		0x00
#define SCREEN2		0x01

extern uint16_t		kscreen[NB_SCREENS][VGA_WIDTH * VGA_HEIGHT];
extern uint16_t		*current_screen;
extern int			current_screen_id;
extern unsigned int	line_count;
extern size_t		line_size;

struct cursor {
	unsigned int	x;
	unsigned int	y;
};

extern struct cursor	cursor[NB_SCREENS];
extern struct cursor	*current_cursor;
extern uint8_t			terminal_color;
extern uint16_t			*terminal_buffer;
extern bool				terminal_show_cursor;


static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) 
{
	return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t color) 
{
	return (uint16_t) uc | (uint16_t) color << 8;
}

static inline unsigned char get_char_at(unsigned int x, unsigned int y)
{
	return (unsigned char) terminal_buffer[x + y * VGA_WIDTH] & 0xFF;
}

static inline unsigned char get_char_at_index(unsigned int index)
{
	return (unsigned char) terminal_buffer[index] & 0xFF;
}

void	terminal_initialize(void);
void	terminal_putentryat(char c, uint8_t color, size_t x, size_t y);
void	terminal_setcolor(uint8_t color);
void	newline();

#endif
