global _start
bits 32
extern kernel_entry

_start:
	jmp .entry

.entry:
	call kernel_entry

