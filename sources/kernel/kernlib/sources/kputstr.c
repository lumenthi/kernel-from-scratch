#include "kernlib.h"

void kputstr(const char* data) 
{
	size_t size = strlen(data);
	for (size_t i = 0; i < size; i++)
		kputchar(data[i]);
}
