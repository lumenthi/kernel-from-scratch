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

#define KPROMPT "[termnial] $ "
#define KPROMPT_SIZE strlen(KPROMPT)

void	outb(uint16_t port, uint8_t val);
void	outw(uint16_t port, uint16_t val);
uint8_t	inb(uint16_t port);

/* ACPI management */
void	poweroff(void);
void	reboot(void);

/* terminal */
void			kputchar(char c);
void			kputstr(const char *s);
void			terminal_putentryat(char c, uint8_t color, size_t x, size_t y);
void			update_cursor();
void			terminal_shift_up();
void			terminal_shift_right();
void			terminal_shift_left();
void			swap_screen();
void			analyze_ansi();

/* utils */
char	*itoa(int value, char *str, int base);
size_t	strlen(const char *s);
void	bzero(void *s, size_t n);
void	*memcpy(void *dst, const void *src, size_t n);
void	*memset(void *b, int c, size_t len);
void	*memmove(void *dst, const void *src, size_t n);
int		strcmp(const char *s1, const char *s2);
int		atoi(const char *str);
int		toupper(int c);
int		tolower(int c);
void	print_bits(void *ptr, size_t bit_size);
void	print_hexa(void *ptr, size_t byte_size);

#endif
