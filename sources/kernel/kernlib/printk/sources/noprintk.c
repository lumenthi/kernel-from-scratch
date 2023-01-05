#include "printk.h"

int			noprintk(const char *restrict format, ...)
{
	t_data	data;

	if (!format)
		return (-1);
	init_data(&data, 1);
	data.mode = NO_PRINT;
	va_start(data.ap, format);
	parse_format(format, &data);
	va_end(data.ap);
	return (data.ret);
}
