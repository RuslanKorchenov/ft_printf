/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnasium <mavrin@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 21:04:26 by vnasium           #+#    #+#             */
/*   Updated: 2020/07/29 21:04:28 by vnasium          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

t_flag		init_flag(t_flag flags)
{
	flags.dot = 0;
	flags.minus = 0;
	flags.precision = -1;
	flags.width = 0;
	flags.zero = 0;
	return (flags);
}

t_flag		parse_stars(va_list ap, t_flag flags)
{
	if (flags.dot == 1)
		flags.precision = va_arg(ap, int);
	else if (flags.width < 1)
	{
		flags.width = va_arg(ap, int);
		if (flags.width < 0)
		{
			flags.minus = 1;
			flags.width *= -1;
		}
	}
	return (flags);
}

t_flag		parse_flags(const char *format, va_list ap, t_flag flags)
{
	int	i;

	i = 0;
	while (format[i] && ft_checkflag(format[i]))
	{
		if (format[i] == '-' && flags.dot == 0)
			flags.minus = 1;
		else if (format[i] == '0' && flags.dot == 0 && flags.width < 1)
			flags.zero = 1;
		else if (ft_isdigit(format[i]) && flags.dot == 0)
			flags.width = (flags.width * 10) + (format[i] - '0');
		else if (ft_isdigit(format[i]) && flags.dot == 1)
			flags.precision = (flags.precision * 10) + (format[i] - '0');
		else if (format[i] == '.')
		{
			flags.dot = 1;
			flags.precision = 0;
		}
		else if (format[i] == '*')
			flags = parse_stars(ap, flags);
		i++;
	}
	return (flags);
}

int			ft_print(char type, t_flag flags, va_list ap)
{
	int	len;

	len = 0;
	if (type == 'c')
		len = ft_print_char(flags, va_arg(ap, int));
	else if (type == 's')
		len = ft_print_string(flags, va_arg(ap, char *), type);
	else if (type == 'p')
		len = ft_print_pointer(flags, va_arg(ap, unsigned long long));
	else if (type == 'd' || type == 'i')
		len = ft_print_int(flags, va_arg(ap, int));
	else if (type == 'u')
		len = ft_print_unsigned(flags, va_arg(ap, unsigned int));
	else if (type == 'x')
		len = ft_print_hex(flags, va_arg(ap, unsigned int), 0);
	else if (type == 'X')
		len = ft_print_hex(flags, va_arg(ap, unsigned int), 1);
	else if (type == '%')
		len = ft_print_percent(flags);
	else
		len = ft_print_char(flags, type);
	return (len);
}

int			ft_printf(const char *format, ...)
{
	va_list		ap;
	int			len;
	int			i;
	t_flag		flags;

	i = 0;
	len = 0;
	va_start(ap, format);
	while (format[i] != '\0')
	{
		if (format[i] == '%' && format[i + 1] != '\0')
		{
			flags = init_flag(flags);
			flags = parse_flags(&format[++i], ap, flags);
			while (ft_checkflag(format[i]))
				i++;
			len += ft_print(format[i], flags, ap);
		}
		else if (format[i] != '%')
			len += ft_putchar(format[i]);
		i++;
	}
	va_end(ap);
	return (len);
}
