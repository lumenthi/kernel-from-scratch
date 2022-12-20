#ifndef KERNEL_H
#define KERNEL_H

/*#define NULL 0

typedef unsigned char	uint8_t;
typedef unsigned short	uint16_t;
typedef unsigned int	uint32_t;
typedef unsigned long	uint64_t;*/

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

extern size_t terminal_row;
extern size_t terminal_column;
extern uint8_t terminal_color;
extern uint16_t* terminal_buffer;
extern bool	terminal_show_cursor;

void	outb(uint16_t port, uint8_t val);
uint8_t	inb(uint16_t port);

char	*itoa(int value, char *str, int base);

void	kputchar(char c);
void	kputstr(const char *s);
void	terminal_putentryat(char c, uint8_t color, size_t x, size_t y);

#endif
