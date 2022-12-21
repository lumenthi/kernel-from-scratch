#include <stddef.h>

void	*memcpy(void *dst, const void *src, size_t n)
{
	size_t		i;
	char		*str;
	const char	*source;

	str = dst;
	source = src;
	i = 0;
	while (i < n)
	{
		str[i] = source[i];
		i++;
	}
	return (dst);
}
