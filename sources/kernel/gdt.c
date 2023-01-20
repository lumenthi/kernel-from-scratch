#include "printk.h"
#include "kernlib.h"
#include "kernel.h"
#include <stdint.h>

#define GDTBASE 0x00000800
#define GDTENTRIES 7

/* Bitwise functions */
#define SEG_DESCTYPE(x) ((x) << 0x04)           /* Descriptor type (0 for system, 1 for code/data) */
#define SEG_PRES(x) ((x) << 0x07)               /* Present */
#define SEG_SAVL(x) ((x) << 0x0C)               /* Available for system use */
#define SEG_LONG(x) ((x) << 0x0D)               /* Long mode */
#define SEG_SIZE(x) ((x) << 0x0E)               /* Size (0 for 16-bit, 1 for 32) */
#define SEG_GRAN(x) ((x) << 0x0F)               /* Granularity (0 for 1B - 1MB, 1 for 4KB - 4GB) */
#define SEG_PRIV(x) (((x) &  0x03) << 0x05)     /* Set privilege level (0 - 3) */

/* Flags values */
#define SEG_DATA_RD        0x00     /* Read-Only */
#define SEG_DATA_RDA       0x01     /* Read-Only, accessed */
#define SEG_DATA_RDWR      0x02     /* Read/Write */
#define SEG_DATA_RDWRA     0x03     /* Read/Write, accessed */
#define SEG_DATA_RDEXPD    0x04     /* Read-Only, expand-down */
#define SEG_DATA_RDEXPDA   0x05     /* Read-Only, expand-down, accessed */
#define SEG_DATA_RDWREXPD  0x06     /* Read/Write, expand-down */
#define SEG_DATA_RDWREXPDA 0x07     /* Read/Write, expand-down, accessed */
#define SEG_CODE_EX        0x08     /* Execute-Only */
#define SEG_CODE_EXA       0x09     /* Execute-Only, accessed */
#define SEG_CODE_EXRD      0x0A     /* Execute/Read */
#define SEG_CODE_EXRDA     0x0B     /* Execute/Read, accessed */
#define SEG_CODE_EXC       0x0C     /* Execute-Only, conforming */
#define SEG_CODE_EXCA      0x0D     /* Execute-Only, conforming, accessed */
#define SEG_CODE_EXRDC     0x0E     /* Execute/Read, conforming */
#define SEG_CODE_EXRDCA    0x0F     /* Execute/Read, conforming, accessed */

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

/* Segments flags */
#define GDT_CODE_PL0 SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | \
                     SEG_LONG(0)     | SEG_SIZE(1) | SEG_GRAN(1) | \
                     SEG_PRIV(0)     | SEG_CODE_EXRD
#define GDT_DATA_PL0 SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | \
                     SEG_LONG(0)     | SEG_SIZE(1) | SEG_GRAN(1) | \
                     SEG_PRIV(0)     | SEG_DATA_RDWR
#define GDT_STACK_PL0 SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | \
                     SEG_LONG(0)     | SEG_SIZE(1) | SEG_GRAN(1) | \
                     SEG_PRIV(0)     | SEG_DATA_RDWREXPD
#define GDT_CODE_PL3 SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | \
                     SEG_LONG(0)     | SEG_SIZE(1) | SEG_GRAN(1) | \
                     SEG_PRIV(3)     | SEG_CODE_EXRD
#define GDT_DATA_PL3 SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | \
                     SEG_LONG(0)     | SEG_SIZE(1) | SEG_GRAN(1) | \
                     SEG_PRIV(3)     | SEG_DATA_RDWR
#define GDT_STACK_PL3 SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | \
                     SEG_LONG(0)     | SEG_SIZE(1) | SEG_GRAN(1) | \
                     SEG_PRIV(3)     | SEG_DATA_RDWREXPD

void install_gdt()
{
	/* NULL */
	gdt_entry(0, 0, 0, 0, 0);
	/* Kernel code */
	gdt_entry(1, 0, 0xFFFFFFFF, (uint8_t)(GDT_CODE_PL0), 0xCF); /* 0x9A */
	/* Kernel data */
	gdt_entry(2, 0, 0xFFFFFFFF, (uint8_t)(GDT_DATA_PL0), 0xCF); /* 0x92 */
	/* Kernel stack */
	gdt_entry(3, 0, 0xFFFFFFFF, (uint8_t)(GDT_STACK_PL0), 0xCF); /* 0x96 */
	/* User code */
	gdt_entry(4, 0, 0xFFFFFFFF, (uint8_t)(GDT_CODE_PL3), 0xCF); /* 0xFA */
	/* User data */
	gdt_entry(5, 0, 0xFFFFFFFF, (uint8_t)(GDT_DATA_PL3), 0xCF); /* 0xF2 */
	/* User stack */
	gdt_entry(6, 0, 0xFFFFFFFF, (uint8_t)(GDT_STACK_PL3), 0xCF); /* 0xF6 */

	_gp.limit = (sizeof(struct gdt_entry) * GDTENTRIES) - 1;
	_gp.base = GDTBASE;

	memcpy((char *)_gp.base, (char *)gdt, _gp.limit);
	_gdt_flush();
}
