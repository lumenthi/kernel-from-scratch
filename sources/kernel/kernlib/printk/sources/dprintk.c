#include "printk.h"

int			dprintk(int fd, const char *restrict format, ...)
{
	t_data	data;

	if (!format)
		return (-1);
	init_data(&data, fd);
	va_start(data.ap, format);
	parse_format(format, &data);
	write(fd, data.buffer, data.i);
	va_end(data.ap);
	return (data.ret);
}
