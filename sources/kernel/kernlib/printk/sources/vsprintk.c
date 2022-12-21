#include "printk.h"

int		vsprintk(char *restrict str, const char *restrict format, va_list ap)
{
	t_data	data;

	if (!format)
		return (-1);
	init_data(&data, 1);
	data.str = str;
	data.mode = STR;
	va_copy(data.ap, ap);
	parse_format(format, &data);
	str[data.i] = '\0';
	return (data.ret);
}
