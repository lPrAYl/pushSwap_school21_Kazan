#include "ft_printf.h"

void	ft_printing_char(t_printf *spec, int c)
{
	if (spec->precision >= -1)
	{
		if (spec->width > 1 && !spec->minus)
			ft_printing_delimeter(spec->width, spec);
		ft_putchar_len(c, spec);
		if (spec->width > 1 && spec->minus)
		{
			spec->zero = 0;
			ft_printing_delimeter(spec->width, spec);
		}
	}
	else
	{
		spec->precision = -spec->precision;
		spec->zero = 0;
		ft_putchar_len(c, spec);
		ft_printing_delimeter(spec->precision, spec);
	}
}

void	ft_printing_percent(t_printf *spec)
{
	if (!spec->minus)
		ft_printing_delimeter(spec->width, spec);
	ft_putchar_len('%', spec);
	if (spec->minus)
	{
		if (spec->precision < -1)
		{
			spec->precision = -spec->precision;
			ft_printing_delimeter(spec->width, spec);
		}
		else
			ft_printing_delimeter(spec->width, spec);
	}
}

void	ft_printing_string(t_printf *spec, char *str)
{
	int	len;

	len = ft_strlen((str));
	if (!str)
		str = "(null)";
	if (spec->precision < 0)
		spec->precision = -1;
	if ((spec->precision < 0 || spec->precision >= len) \
													&& !spec->minus)
		ft_printing_delimeter(spec->width - len + 1, spec);
	else if (spec->precision != -1 && !spec->minus)
		ft_printing_delimeter(spec->width - spec->precision + 1, spec);
	ft_putstr_spec(str, spec);
	if ((spec->precision == -1 || spec->precision >= len) \
														&& spec->minus)
		ft_printing_delimeter(spec->width - len + 1, spec);
	else if (spec->precision != -1 && spec->minus)
		ft_printing_delimeter(spec->width - spec->precision + 1, spec);
}
