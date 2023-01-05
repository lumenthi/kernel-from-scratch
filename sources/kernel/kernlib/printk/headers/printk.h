#ifndef PRINTK_H
# define PRINTK_H
# include <unistd.h>
# include <stdarg.h>
# define BUFF_SIZE 4096

typedef enum		e_modes
{
	STDOUT,
	STR_SIZE,
	STR,
	NO_PRINT
}					t_modes;

typedef struct		s_padding
{
	int				left_spaces;
	int				sign;
	int				zeros;
	int				size;
	int				right_spaces;
}					t_padding;

typedef struct		s_data
{
	va_list			ap;
	char			buffer[BUFF_SIZE];
	int				i;
	int				fd;
	int				left;
	int				plus;
	int				zero;
	int				space;
	int				sharp;
	int				l_min;
	int				prec;
	int				size;
	int				ret;
	int				mode;
	const char		*invalid;
	char *restrict	str;
	size_t			str_size;
	t_padding		padding;
	char			padding_var[4];
}					t_data;

int					printk(const char *restrict format, ...);
int					bprintk(int force_flush, const char *restrict format, ...);
int					noprintk(const char *restrict format, ...);
int					vprintk(const char *restrict format, va_list ap);
int					dprintk(int fd, const char *restrict format, ...);
int					sprintk(char *restrict str,
const char *restrict format, ...);
int					vsprintk(char *restrict str,
const char *restrict format, va_list ap);
int					snprintk(char *restrict str, size_t size,
const char *restrict format, ...);
int					vsnprintk(char *restrict str, size_t size,
const char *restrict format, va_list ap);
void				init_data(t_data *data, int fd);
void				parse_format(const char *restrict format, t_data *data);
void				pf_putchar(t_data *data);
void				pf_putfloat(t_data *data);
void				pf_putnbr(t_data *data);
void				pf_putunbr(t_data *data);
void				pf_putstr(t_data *data);
void				pf_putaddr(t_data *data);
void				pf_putnbr_x(t_data *data);
void				pf_putnbr_xcaps(t_data *data);
void				pf_putnbr_o(t_data *data);
void				pf_putnbr_b(t_data *data);
void				pf_putlong_base(unsigned long nbr, char *base,
t_data *data);
void				pf_invalid(t_data *data);
void				pf_putpercent(t_data *data);
void				fill_buffer(t_data *data, const char *s, unsigned int size);
char				parse_flags(const char *s, int *i, t_data *data);
void				parse_color(const char *s, int *i, t_data *data);
int					pf_atoi(const char *str);
void				reset_options(t_data *data);
int					pf_strnequ(char const *s1, char const *s2, size_t n);
void				set_fpadding_lmin(t_data *data);
void				set_fpadding(t_data *data, long i_part, long double nb);
void				set_fpadding_inf(t_data *data, long double nb);
int					inf(t_data *data, long double nb);
long double			cast_float(t_data *data);
int					get_size(long nbr);
long double			power(long double nb, int power);
char				*pf_strnew(int size, t_data *data);
void				rev_str(char *str, int len);
void				pf_strdel(char **ap);
void				parse_options(const char *s, int *i, t_data *data);
void				parse_l_min(const char *s, int *i, t_data *data);
void				parse_prec(const char *s, int *i, t_data *data);
void				parse_size(const char *s, int *i, t_data *data);
void				parse_wildcard(int *i, t_data *data);

#endif
