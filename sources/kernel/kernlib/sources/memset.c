#include <stddef.h>

void	*memset(void *b, int c, size_t len)
{
	size_t			i;
	char			*str;
	unsigned char	cchar;

	i = 0;
	str = b;
	cchar = c;
	while (i < len)
	{
		str[i] = cchar;
		i++;
	}
	return (b);
}
