#include "ft_printf.h"

void	ft_printing_zeroes(int width, t_printf *spec)
{
	while (--width > 0)
		ft_putchar_len('0', spec);
}

void	ft_special_case_number(t_printf *spec)
{
	if (spec->zero)
	{
		spec->zero = 0;
		ft_printing_delimeter(spec->width + 1, spec);
	}
	else
		ft_printing_delimeter(spec->width + 1, spec);
}

void	ft_printing_unsigned_number_base(t_printf *spec, unsigned int nbr)
{
	char		*str;

	if (nbr == 0 && spec->precision == 0)
	{
		ft_special_case_number(spec);
		return ;
	}
	if (spec->precision > -1)
		spec->zero = 0;
	if (spec->type == 'x' || spec->type == 'X')
		spec->base = 16;
	str = ft_itoa_base(nbr, spec);
	if (spec->precision <= (int)ft_strlen(str))
		spec->precision = ft_strlen(str);
	if (!spec->minus)
		ft_printing_delimeter(spec->width - spec->precision + 1, spec);
	if (spec->plus)
		ft_putchar_len('+', spec);
	else if (spec->space)
		ft_putchar_len(' ', spec);
	ft_printing_zeroes(spec->precision - ft_strlen(str) + 1, spec);
	ft_putstr_spec(str, spec);
	if (spec->minus)
		ft_printing_delimeter(spec->width - spec->precision + 1, spec);
	free(str);
}

void	ft_printing_number(t_printf *spec, long long nbr)
{
	char	*str;

	if (nbr >= 0)
		ft_printing_unsigned_number_base(spec, nbr);
	else
	{
		nbr = -nbr;
		str = ft_itoa_base(nbr, spec);
		if (spec->precision > -1)
			spec->zero = 0;
		if (spec->precision <= (int)ft_strlen(str))
			spec->precision = ft_strlen(str);
		if (spec->zero)
			ft_putchar_len('-', spec);
		if (!spec->minus)
			ft_printing_delimeter(spec->width - spec->precision, spec);
		if (!spec->zero)
			ft_putchar_len('-', spec);
		ft_printing_zeroes(spec->precision - ft_strlen(str) + 1, spec);
		ft_putstr_spec(str, spec);
		if (spec->minus)
			ft_printing_delimeter(spec->width - spec->precision, spec);
		free(str);
	}
}
