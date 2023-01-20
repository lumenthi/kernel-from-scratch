#include "kernlib.h"
#include "printk.h"

#define STACK_VALUES 64

void print_stack(void)
{
	register uint32_t *esp asm("esp");
	int i = 0;
	while (i < STACK_VALUES) {
		printk("0x%08x  ", esp[i]);
		if ((i+1) % 4 == 0)
			printk("\n");
		i++;
	}
}
