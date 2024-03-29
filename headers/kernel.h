#ifndef KERNEL_H
#define KERNEL_H

/* #define NULL 0

typedef unsigned char	uint8_t;
typedef unsigned short	uint16_t;
typedef unsigned int	uint32_t;
typedef unsigned long	uint64_t; */

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "kernlib.h"

#define debug_stack(bytes) printk("\n");register uint32_t *esp asm("esp");dump_mem(esp, bytes)

void	install_gdt(void);

#endif
