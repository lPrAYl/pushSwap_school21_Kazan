#include "ft_printf.h"

void	ft_putchar_len(char c, t_printf *spec)
{
	write (1, &c, 1);
	spec->lenght++;
}

void	ft_putstr_spec(char *str, t_printf *spec)
{
	unsigned int	i;
	unsigned int	len;

	if (!str)
		return ;
	i = 0;
	if (spec->precision == -1 || spec->precision >= (int)ft_strlen(str))
		len = ft_strlen(str);
	else
	{
		if (spec->precision < 1)
			spec->precision = 0;
		len = spec->precision;
	}
	while (i < len)
	{
		ft_putchar_len(*(str + i), spec);
		i++;
	}
}

void	ft_printing_delimeter(int width, t_printf *spec)
{
	while (--width > 0)
	{
		if (spec->zero && !spec->minus)
			ft_putchar_len('0', spec);
		else
			ft_putchar_len(' ', spec);
	}
}

int	ft_isdigit_minus(int c)
{
	if ((c > 47 && c < 58) || c == '-')
		return (1);
	return (0);
}
