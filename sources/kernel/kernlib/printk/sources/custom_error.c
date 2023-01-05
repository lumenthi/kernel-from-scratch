#include "printk.h"

int			custom_error(const char *restrict format, ...)
{
	t_data	data;

	if (!format)
		return (-1);
	init_data(&data, 1);
	va_start(data.ap, format);
	parse_format(format, &data);
	write(STDERR_FILENO, data.buffer, data.i);
	va_end(data.ap);
	return (-1);
}
