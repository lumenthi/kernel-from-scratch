#include "printk.h"
#include "kernlib.h"
#include "kernel.h"
#include <stdint.h>

#define GDTBASE 0x00000800
#define GDTENTRIES 5

struct gdt_entry
{
	unsigned short limit_low;
	unsigned short base_low;
	unsigned char base_middle;
	unsigned char access;
	unsigned char granularity;
	unsigned char base_high;
} __attribute__((packed));

struct gdt_ptr
{
	unsigned short limit;
	unsigned int base;
} __attribute__((packed));

struct gdt_entry	gdt[GDTENTRIES];
struct gdt_ptr		_gp;
extern void			_gdt_flush(void);

static void gdt_entry(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran)
{
	gdt[num].base_low = (base & 0xFFFF);
	gdt[num].base_middle = (base >> 16) & 0xFF;
	gdt[num].base_high = (base >> 24) & 0xFF;
	gdt[num].limit_low = (limit & 0xFFFF);
	gdt[num].granularity = ((limit >> 16) & 0x0F);
	gdt[num].granularity |= (gran & 0xF0);
	gdt[num].access = access;
}

void install_gdt()
{
	/* NULL */
	gdt_entry(0, 0, 0, 0, 0);
	/* Code segment */
	gdt_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
	/* Data segment */
	gdt_entry(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
	/* User code */
	gdt_entry(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);
	/* User data */
	gdt_entry(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);

	_gp.limit = (sizeof(struct gdt_entry) * GDTENTRIES) - 1;
	_gp.base = GDTBASE;

	memcpy((char *)_gp.base, (char *)gdt, _gp.limit);
	_gdt_flush();
}
