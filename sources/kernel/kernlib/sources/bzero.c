#include "kernlib.h"

void	bzero(void *s, size_t n)
{
	if (n > 0)
		memset(s, 0, n);
}
