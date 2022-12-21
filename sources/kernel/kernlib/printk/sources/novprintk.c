#include "printk.h"

int			novprintk(const char *restrict format, va_list ap)
{
	t_data	data;

	if (!format)
		return (-1);
	init_data(&data, 1);
	data.mode = NO_PRINT;
	va_copy(data.ap, ap);
	parse_format(format, &data);
	return (data.ret);
}
