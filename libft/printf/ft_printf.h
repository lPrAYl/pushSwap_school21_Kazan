#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include "../libft.h"

typedef struct s_printf
{
	char	type;
	int		minus;
	int		plus;
	int		zero;
	int		space;
	int		width;
	int		precision;
	int		iterator;
	int		base;
	int		lenght;
}			t_printf;

int			ft_printf(const char *format, ...);

void		ft_putchar_len(char c, t_printf *spec);
int			ft_isdigit_minus(int c);
void		ft_printing_delimeter(int width, t_printf *spec);
void		ft_putstr_spec(char *str, t_printf *spec);
char		*ft_itoa_base(unsigned long nbr, t_printf *spec);
int			ft_len_nbr(unsigned long nbr, int sign, int base);
int			ft_abs_nbr(int nbr);
void		ft_printing_zeroes(int width, t_printf *spec);
void		ft_putstr_spec_0x(t_printf *spec);
void		ft_special_case_pointer(t_printf *spec);
void		ft_special_case_number(t_printf *spec);
char		ft_char_from_itoa(int digit, t_printf *spec);

t_printf	ft_spec_init(t_printf *spec);
void		ft_flag_parsing(const char *format, t_printf *spec);
void		ft_width_parsing(const char *format, t_printf *spec, va_list ap);
void		ft_prec_parsing(const char *format, t_printf *spec, va_list ap);
void		ft_type_parsing(const char *format, t_printf *spec);
void		ft_format_parsing(const char *format, va_list ap, t_printf *spec);

void		ft_printing(t_printf *spec, va_list ap);
void		ft_printing_char(t_printf *spec, int c);
void		ft_printing_percent(t_printf *spec);
void		ft_printing_string(t_printf *spec, char *str);
void		ft_printing_number(t_printf *spec, long long nbr);
void		ft_printing_unsigned_number_base(t_printf *spec, unsigned int nbr);
void		ft_printing_pointer(t_printf *spec, unsigned long nbr);

#endif