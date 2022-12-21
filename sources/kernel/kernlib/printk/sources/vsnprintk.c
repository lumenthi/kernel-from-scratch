#include "printk.h"

int		vsnprintk(char *restrict str, size_t size,
const char *restrict format, va_list ap)
{
	t_data	data;

	if (!format)
		return (-1);
	init_data(&data, 1);
	va_copy(data.ap, ap);
	data.str = str;
	data.str_size = size;
	data.mode = STR;
	parse_format(format, &data);
	str[data.i] = '\0';
	return (data.ret);
}
