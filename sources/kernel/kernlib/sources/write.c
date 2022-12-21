#include "kernlib.h"
#include <sys/types.h>

ssize_t	write(int fd, const void *buf, size_t count)
{
	char	*s;

	(void)fd;
	s = (char*)buf;
	for (size_t i = 0; i < count; i++)
		kputchar(s[i]);
}
