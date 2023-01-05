#include "printk.h"

int		sprintk(char *restrict str, const char *restrict format, ...)
{
	t_data	data;

	if (!format)
		return (-1);
	init_data(&data, 1);
	data.str = str;
	data.mode = STR;
	va_start(data.ap, format);
	parse_format(format, &data);
	str[data.i] = '\0';
	va_end(data.ap);
	return (data.ret);
}
