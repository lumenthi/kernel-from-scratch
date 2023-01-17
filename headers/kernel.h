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
#include "kernlib.h"

extern void	init_gdt(void);
extern void	load_gdt(uint32_t base, uint16_t limit);

#endif
