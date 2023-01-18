global _gdt_flush; Allows the C code to link to this
extern _gp; Says that '_gp' is in another file
_gdt_flush:
	lgdt [_gp]; Load the GDT with our '_gp' which is a special pointer
	; 0x10 is the offset to our kernel data segment, let's load all data
	;	segment selectors
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	jmp 0x08:_ret; 0x08 is the offset to our code segment

_ret:
	ret; jump back to the C code!
