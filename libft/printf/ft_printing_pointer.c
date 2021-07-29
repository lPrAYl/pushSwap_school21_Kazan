#include "ft_printf.h"

void	ft_putstr_spec_0x(t_printf *spec)
{
	ft_putchar_len('0', spec);
	ft_putchar_len('x', spec);
}

void	ft_special_case_pointer(t_printf *spec)
{
	if (spec->precision == 0)
	{
		if (!spec->minus)
			ft_printing_delimeter(spec->width - 1, spec);
		spec->precision = -1;
		ft_putstr_spec("0x", spec);
		if (spec->minus)
			ft_printing_delimeter(spec->width - 1, spec);
	}
	else
	{
		if (!spec->minus)
			ft_printing_delimeter(spec->width - 2, spec);
		spec->precision = -1;
		ft_putstr_spec("0x0", spec);
		if (spec->minus)
			ft_printing_delimeter(spec->width - 2, spec);
	}
}

void	ft_printing_pointer(t_printf *spec, unsigned long nbr)
{
	char	*str;

	if (nbr == 0 && spec->precision <= 0)
	{
		ft_special_case_pointer(spec);
		return ;
	}
	if (spec->precision > -1)
		spec->zero = 0;
	spec->base = 16;
	str = ft_itoa_base(nbr, spec);
	if (spec->precision <= (int)ft_strlen(str))
		spec->precision = ft_strlen(str);
	if (!spec->minus)
		ft_printing_delimeter(spec->width - spec->precision - 1, spec);
	ft_putstr_spec_0x(spec);
	ft_printing_zeroes(spec->precision - ft_strlen(str) + 1, spec);
	ft_putstr_spec(str, spec);
	if (spec->minus)
		ft_printing_delimeter(spec->width - spec->precision - 1, spec);
	free (str);
}
