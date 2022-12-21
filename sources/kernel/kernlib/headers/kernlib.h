#ifndef KERNLIB_H
#define KERNLIB_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

//#define NULL 0

/*typedef unsigned char	uint8_t;
typedef unsigned short	uint16_t;
typedef unsigned int	uint32_t;
typedef unsigned long	uint64_t;
typedef int				bool;*/

extern size_t terminal_row;
extern size_t terminal_column;
extern uint8_t terminal_color;
extern uint16_t* terminal_buffer;
extern bool	terminal_show_cursor;

void	outb(uint16_t port, uint8_t val);
uint8_t	inb(uint16_t port);

/* terminal */
void	kputchar(char c);
void	kputstr(const char *s);
void	terminal_putentryat(char c, uint8_t color, size_t x, size_t y);
void	update_cursor(int x, int y);

char	*itoa(int value, char *str, int base);
size_t	strlen(const char *s);
void	bzero(void *s, size_t n);
void	*memcpy(void *dst, const void *src, size_t n);
void	*memset(void *b, int c, size_t len);
void	*memmove(void *dst, const void *src, size_t n);

#endif
