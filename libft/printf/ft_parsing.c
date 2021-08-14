#include "ft_printf.h"

t_printf	ft_spec_init(t_printf *spec)
{
	spec->type = '~';
	spec->minus = 0;
	spec->plus = 0;
	spec->space = 0;
	spec->zero = 0;
	spec->width = 0;
	spec->precision = -1;
	spec->iterator = 0;
	spec->base = 10;
	return (*spec);
}

void	ft_flag_parsing(const char *format, t_printf *spec)
{
	size_t	i;

	i = 0;
	while (1)
	{
		if (*(format + i) == '-')
			spec->minus = 1;
		else if (*(format + i) == '+')
			spec->plus = 1;
		else if (*(format + i) == ' ')
			spec->space = 1;
		else if (*(format + i) == '0')
			spec->zero = 1;
		else
			break ;
		++i;
	}
	spec->iterator = i;
}

void	ft_width_parsing(const char *format, t_printf *spec, va_list ap)
{
	if (*(format + spec->iterator) == '*')
	{
		spec->width = va_arg(ap, int);
		if (spec->width < 0)
		{
			spec->width *= -1;
			spec->minus = 1;
		}
		spec->iterator++;
		return ;
	}
	spec->width = ft_atoi((char *)format + spec->iterator);
	while (ft_isdigit_minus(*(format + spec->iterator)))
		spec->iterator++;
}

void	ft_prec_parsing(const char *format, t_printf *spec, va_list ap)
{
	if (*(format + spec->iterator) == '.')
		spec->iterator++;
	else
		return ;
	if (*(format + spec->iterator) == '-')
		spec->minus = 1;
	if (*(format + spec->iterator) == '*')
	{
		spec->precision = va_arg(ap, int);
		spec->iterator++;
		return ;
	}
	spec->precision = ft_atoi((char *)format + spec->iterator);
	while (ft_isdigit_minus(*(format + spec->iterator)))
		spec->iterator++;
}

void	ft_type_parsing(const char *format, t_printf *spec)
{
	if (*(format + spec->iterator))
	{
		spec->type = *(format + spec->iterator);
		spec->iterator++;
	}
}
