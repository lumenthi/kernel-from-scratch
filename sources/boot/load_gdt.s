gdtr DW 0
     DD 0

global load_gdt
load_gdt:
	mov		ax, [esp + 4]
	mov		[gdtr], ax
	mov		eax, [esp + 8]
	mov		[gdtr + 2], eax
	lgdt	[gdtr]
	ret
