#include "printk.h"
#include "put_padding.h"

static void	set_padding(t_data *data)
{
	data->padding.zeros = 0;
	if (!data->left && data->zero)
		data->padding.zeros = data->l_min - 1;
	if (data->padding.zeros < 0)
		data->padding.zeros = 0;
	data->padding.right_spaces = 0;
	data->padding.left_spaces = 0;
	if (data->left)
		data->padding.right_spaces = data->l_min - data->padding.zeros - 1;
	else
		data->padding.left_spaces = data->l_min - data->padding.zeros - 1;
}

void		pf_putpercent(t_data *data)
{
	set_padding(data);
	put_left_spaces(data);
	put_zeros(data);
	fill_buffer(data, "%", 1);
	put_right_spaces(data);
}
