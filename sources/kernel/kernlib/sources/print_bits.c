#include "printk.h"
#include <stdint.h>

void	print_bits(void *ptr, size_t bit_size)
{
	uint8_t *in = (uint8_t*)(ptr + bit_size / 8 - 1);
	uint8_t	c;
	size_t i = 0;
	while (i < bit_size)
	{
		c = *in;
		size_t j = 0;
		while (j < 8 && i < bit_size)
		{
			printk("%d", (c >> (8 - j - 1)) & 1);
			i++;
			j++;
		}
		/*printk("%.2X", c);
		i+=8;*/
		in--;
	}
}
