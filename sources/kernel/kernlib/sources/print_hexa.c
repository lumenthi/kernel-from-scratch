#include "printk.h"
#include <stdint.h>

void	print_hexa(void *ptr, size_t byte_size)
{
	uint8_t *in = (uint8_t*)(ptr + byte_size - 1);
	uint8_t	c;
	for (size_t i = 0; i < byte_size; i++)
	{
		c = *in;
		printk("%.2X", c);
		in--;
	}
}
