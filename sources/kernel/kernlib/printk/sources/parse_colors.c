#include "printk.h"
#include "color.h"

void	put_colors_4(const char *s, int *i, t_data *data)
{
	if (pf_strnequ(s + *i, "{bcyan}", 7) == 1)
	{
		fill_buffer(data, BCYAN, 5);
		(*i) += 6;
	}
	if (pf_strnequ(s + *i, "{byellow}", 9) == 1)
	{
		fill_buffer(data, BYELLOW, 5);
		(*i) += 8;
	}
	else if (pf_strnequ(s + *i, "{bblue}", 7) == 1)
	{
		fill_buffer(data, BBLUE, 5);
		(*i) += 6;
	}
	else if (pf_strnequ(s + *i, "{bmagenta}", 10) == 1)
	{
		fill_buffer(data, BMAGENTA, 5);
		(*i) += 9;
	}
	else if (pf_strnequ(s + *i, "{black}", 7) == 1)
	{
		fill_buffer(data, BLACK, 5);
		(*i) += 6;
	}
	else if (pf_strnequ(s + *i, "{bblack}", 8) == 1)
	{
		fill_buffer(data, BBLACK, 5);
		(*i) += 7;
	}
	else if (pf_strnequ(s + *i, "{blink}", 7) == 1)
	{
		fill_buffer(data, BLINK, 5);
		(*i) += 7;
	}
	else if (pf_strnequ(s + *i, "{concealed}", 11) == 1)
	{
		fill_buffer(data, CONCEALED, 5);
		(*i) += 7;
	}
	else if (pf_strnequ(s + *i, "{white}", 7) == 1)
	{
		fill_buffer(data, WHITE, 5);
		(*i) += 7;
	}
	else if (pf_strnequ(s + *i, "{bwhite}", 8) == 1)
	{
		fill_buffer(data, BWHITE, 5);
		(*i) += 7;
	}
}

void	put_colors_3(const char *s, int *i, t_data *data)
{
	if (pf_strnequ(s + *i, "{bold}", 6) == 1)
	{
		fill_buffer(data, BOLD, 4);
		(*i) += 5;
	}
	else if (pf_strnequ(s + *i, "{invert}", 8) == 1)
	{
		fill_buffer(data, INVERT, 4);
		(*i) += 7;
	}
	if (pf_strnequ(s + *i, "{bred}", 6) == 1)
	{
		fill_buffer(data, BRED, 5);
		(*i) += 5;
	}
	else if (pf_strnequ(s + *i, "{bgreen}", 8) == 1)
	{
		fill_buffer(data, BGREEN, 5);
		(*i) += 7;
	}
	else
		put_colors_4(s, i, data);
}

void	put_colors_2(const char *s, int *i, t_data *data)
{
	if (pf_strnequ(s + *i, "{yellow}", 8) == 1)
	{
		fill_buffer(data, YELLOW, 5);
		(*i) += 7;
	}
	else if (pf_strnequ(s + *i, "{blue}", 6) == 1)
	{
		fill_buffer(data, BLUE, 5);
		(*i) += 5;
	}
	else if (pf_strnequ(s + *i, "{magenta}", 9) == 1)
	{
		fill_buffer(data, MAGENTA, 5);
		(*i) += 8;
	}
	else if (pf_strnequ(s + *i, "{underline}", 11) == 1)
	{
		fill_buffer(data, UNDERLINE, 4);
		(*i) += 10;
	}
	else
		put_colors_3(s, i, data);
}

void	put_colors(const char *s, int *i, t_data *data)
{
	if (pf_strnequ(s + *i, "{red}", 5) == 1)
	{
		fill_buffer(data, RED, 5);
		(*i) += 4;
	}
	else if (pf_strnequ(s + *i, "{green}", 7) == 1)
	{
		fill_buffer(data, GREEN, 5);
		(*i) += 6;
	}
	else if (pf_strnequ(s + *i, "{cyan}", 6) == 1)
	{
		fill_buffer(data, CYAN, 5);
		(*i) += 5;
	}
	else if (pf_strnequ(s + *i, "{reset}", 7) == 1)
	{
		fill_buffer(data, RESET, 4);
		(*i) += 6;
	}
	else
		put_colors_2(s, i, data);
}

void	parse_color(const char *s, int *i, t_data *data)
{
	if (pf_strnequ(s + *i, "{reset}", 7) == 1
		|| pf_strnequ(s + *i, "{bold}", 6) == 1
		|| pf_strnequ(s + *i, "{underline}", 11) == 1
		|| pf_strnequ(s + *i, "{blink}", 7) == 1
		|| pf_strnequ(s + *i, "{invert}", 8) == 1
		|| pf_strnequ(s + *i, "{concealed}", 11) == 1

		|| pf_strnequ(s + *i, "{black}", 7) == 1
		|| pf_strnequ(s + *i, "{red}", 5) == 1
		|| pf_strnequ(s + *i, "{green}", 7) == 1
		|| pf_strnequ(s + *i, "{yellow}", 8) == 1
		|| pf_strnequ(s + *i, "{blue}", 6) == 1
		|| pf_strnequ(s + *i, "{magenta}", 9) == 1
		|| pf_strnequ(s + *i, "{cyan}", 6) == 1
		|| pf_strnequ(s + *i, "{white}", 7) == 1

		|| pf_strnequ(s + *i, "{bblack}", 8) == 1
		|| pf_strnequ(s + *i, "{bred}", 6) == 1
		|| pf_strnequ(s + *i, "{bgreen}", 8) == 1
		|| pf_strnequ(s + *i, "{byellow}", 9) == 1
		|| pf_strnequ(s + *i, "{bblue}", 7) == 1
		|| pf_strnequ(s + *i, "{bmagenta}", 10) == 1
		|| pf_strnequ(s + *i, "{bcyan}", 7) == 1
		|| pf_strnequ(s + *i, "{bwhite}", 8) == 1)
	{
		if ((*i > 0 && s[*i - 1] != '{') || *i == 0)
			put_colors(s, i, data);
	}
	else
		fill_buffer(data, s + *i, 1);
}
