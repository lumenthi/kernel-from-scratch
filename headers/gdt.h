#ifndef GDT_H
#define GDT_H

struct GDT {
	uint32_t	base;
	uint16_t	limit;
	uint8_t		access_bytes;
	uint8_t		flags;
};

#endif
