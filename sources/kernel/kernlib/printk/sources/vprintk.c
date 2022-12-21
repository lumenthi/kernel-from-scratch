#include "printk.h"

int			vprintk(const char *restrict format, va_list ap)
{
	t_data	data;

	if (!format)
		return (-1);
	init_data(&data, 1);
	va_copy(data.ap, ap);
	parse_format(format, &data);
	write(1, data.buffer, data.i);
	return (data.ret);
}
