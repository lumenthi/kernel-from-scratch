#include "kernlib.h"
#include "printk.h"

void dump_mem(uint32_t *esp, uint32_t values)
{
	int i = 0;

	while (i < values) {
		if ((i) % 4 == 0)
			printk("{cyan}0x%08x: {reset}", esp+i);
		printk("0x%08x  ", esp[i]);
		if ((i+1) % 4 == 0)
			printk("\n");
		i++;
	}
}

void print_stack(void)
{
	register uint32_t *esp asm("esp");
	dump_mem(esp, 64);
}
