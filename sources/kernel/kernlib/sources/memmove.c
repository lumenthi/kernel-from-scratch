#include "kernlib.h"

void	*memmove(void *dst, const void *src, size_t n)
{
	char		*tmp;
	const char	*source;

	tmp = dst;
	source = src;
	if (dst > src)
	{
		while (n > 0)
		{
			tmp[n - 1] = source[n - 1];
			n--;
		}
	}
	else
		memcpy(dst, src, n);
	return (dst);
}
