#include "ft_printf.h"

void	ft_format_parsing(const char *format, va_list ap, t_printf *spec)
{
	*spec = ft_spec_init(spec);
	ft_flag_parsing(format, spec);
	ft_width_parsing(format, spec, ap);
	ft_prec_parsing(format, spec, ap);
	ft_type_parsing(format, spec);
}

void	ft_printing(t_printf *spec, va_list ap)
{
	if (spec->type == 'c')
		ft_printing_char(spec, va_arg(ap, int));
	else if (spec->type == '%')
		ft_printing_percent(spec);
	else if (spec->type == 's')
		ft_printing_string(spec, va_arg(ap, char *));
	else if (spec->type == 'i' || spec->type == 'd')
		ft_printing_number(spec, va_arg(ap, int));
	else if (spec->type == 'x' || spec->type == 'X' || spec->type == 'u')
		ft_printing_unsigned_number_base(spec, va_arg(ap, unsigned int));
	else if (spec->type == 'p')
		ft_printing_pointer(spec, va_arg(ap, unsigned long));
}

int	ft_printf(const char *format, ...)
{
	size_t			i;
	va_list			ap;
	t_printf		spec;

	i = 0;
	spec.lenght = 0;
	va_start(ap, format);
	while (*(format + i))
	{
		if (*(format + i) != '%')
			ft_putchar_len(*(format + i), &spec);
		else if (*(format + i) == '%')
		{
			ft_format_parsing(format + i + 1, ap, &spec);
			ft_printing(&spec, ap);
			i += spec.iterator;
		}
		++i;
	}
	va_end(ap);
	return (spec.lenght);
}
