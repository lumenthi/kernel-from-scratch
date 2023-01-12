#include "printk.h"
#include "kernlib.h"
#include <stdint.h>

#define ACCESS_P(X)		(X >> 7) & 1
#define ACCESS_DPL(X)	(X >> 6) & 1
#define ACCESS_S(X)		(X >> 4) & 1
#define ACCESS_E(X)		(X >> 3) & 1
#define ACCESS_DC(X)	(X >> 2) & 1
#define ACCESS_RW(X)	(X >> 1) & 1
#define ACCESS_A(X)		(X >> 0) & 1

#define FLAG_G(X)		(X >> 3) & 1
#define FLAG_DB(X)		(X >> 2) & 1
#define FLAG_L(X)		(X >> 1) & 1

static void	print_gdt_entry(uint64_t gdt_entry)
{
	printk("-- Struct view --\n");
	printk("Base 24-31:  0x%.2llX\n", (gdt_entry >> 56) & 0xFF);
	printk("Flags:       0x%.1llX\n", (gdt_entry >> 52) & 0xF);
	printk("Limit 16-19: 0x%.1llX\n", (gdt_entry >> 48) & 0xF);
	printk("Access byte: 0x%.2llX\n", (gdt_entry >> 40) & 0xFF);
	printk("Base 16-23:  0x%.2llX\n", (gdt_entry >> 32) & 0xFF);
	printk("Base 0-15:   0x%.4llX\n", (gdt_entry >> 16) & 0xFFFF);
	printk("Limit 0-15:  0x%.4llX\n", gdt_entry & 0xFFFF);

	printk("-- Value view --\n");
	/* Retrieve base value */
	uint32_t base = 0;
	base |= (gdt_entry >> 56) & 0xFF;
	base <<= 24;
	base |= (gdt_entry >> 16) & 0xFFFFFF;
	printk("Base = 0x%.8llX\n", base);

	/* Retrieve limit value */
	uint32_t limit = 0;
	limit |= (gdt_entry >> 48) & 0xF;
	limit <<= 16;
	limit |= gdt_entry & 0xFFFF;
	printk("Limit = 0x%.5llX\n", limit);

	/* Retrieve access byte */
	uint8_t access_byte = (gdt_entry >> 40) & 0xFF;
	printk("Access byte:\n");
	printk("| P = %d | DPL = %d | S = %d | E = %d | DC = %d | RW = %d | A = %d |\n",
		ACCESS_P(access_byte), ACCESS_DPL(access_byte), ACCESS_S(access_byte),
		ACCESS_E(access_byte), ACCESS_DC(access_byte), ACCESS_RW(access_byte),
		ACCESS_A(access_byte));

	/* Retrieve flags */
	uint8_t flags = (gdt_entry >> 52) & 0xF;
	printk("Flags:\n");
	printk("| G = %d | DB = %d | L = %d | Reserved |\n",
		FLAG_G(flags), FLAG_DB(flags), FLAG_L(flags));
}

static uint8_t	create_access_byte(uint8_t P, uint8_t DPL, uint8_t S, uint8_t E,
	uint8_t DC, uint8_t RW, uint8_t A)
{
	uint8_t	access_byte = 0;

	access_byte |= P;
	access_byte <<= 1;
	access_byte |= DPL;
	access_byte <<= 2;
	access_byte |= S;
	access_byte <<= 1;
	access_byte |= E;
	access_byte <<= 1;
	access_byte |= DC;
	access_byte <<= 1;
	access_byte |= RW;
	access_byte <<= 1;
	access_byte |= A;

	return access_byte;
}
static uint8_t	create_flags(uint8_t G, uint8_t DB, uint8_t L)
{
	uint8_t	flags = 0;

	flags |= G;
	flags <<= 1;
	flags |= DB;
	flags <<= 1;
	flags |= L;
	flags <<= 1; // Shift for the last reserved byte ( = 0 )

	return flags;
}

static void gdt_entry(uint8_t *target, uint32_t base, uint32_t limit, uint8_t flags, uint8_t access_byte)
{
	/* GDT Entry:
	 * |63    56|55 52|51 48|47    40|39      32|
	 * |  Base  |Flags|Limit| Access |   Base   |
	 * |31                16|15                0|
	 * |        Base        |       Limit       |
	 */

    // Limit
    target[0] = limit & 0xFF;
    target[1] = (limit >> 8) & 0xFF;
    target[6] = (limit >> 16) & 0x0F;

    // Base
    target[2] = base & 0xFF;
    target[3] = (base >> 8) & 0xFF;
    target[4] = (base >> 16) & 0xFF;
    target[7] = (base >> 24) & 0xFF;

    // Access byte
    target[5] = access_byte;

    // Flags
    target[6] |= (flags << 4);
	
	uint64_t entry = *(uint64_t*)target;
	print_gdt_entry(entry);
}

void	init_gdt(void)
{
	printk("\nNull entry:\n");
	gdt_entry((void*)0x00000800, 0, 0, 0, 0);
	printk("\nSecond entry:\n");
	gdt_entry((void*)0x00000808, 0x12345678, 0, create_flags(0, 0, 1),
		create_access_byte(1, 0, 1, 1, 0, 1, 0));
}
