/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_d_i_u.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnasium <mavrin@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 21:03:49 by vnasium           #+#    #+#             */
/*   Updated: 2020/07/29 21:03:49 by vnasium          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static	t_flag	define_flags(t_flag flags, int negative)
{
	if (((flags.dot && flags.precision >= 0) || flags.width < 0 || flags.minus)
	&& flags.zero)
		flags.zero = 0;
	if (flags.zero)
	{
		if (flags.width > 0)
			flags.precision = flags.width;
		if (negative)
			flags.precision--;
		flags.width = 0;
	}
	return (flags);
}

int				ft_print_int(t_flag flags, int value)
{
	int		len;
	char	*num_str;

	flags = define_flags(flags, value < 0);
	if (flags.dot && (value == 0) && (flags.precision == 0))
		num_str = ft_strdup("");
	else
		num_str = ft_itoa_precision(value, flags.precision);
	len = ft_print_string(flags, num_str, 'd');
	free(num_str);
	return (len);
}

int				ft_print_unsigned(t_flag flags, unsigned int value)
{
	int		len;
	char	*num_str;

	flags = define_flags(flags, 0);
	if (flags.dot && (value == 0) && (flags.precision == 0))
		num_str = ft_strdup("");
	else
		num_str = ft_itoa_base_precision(value, flags.precision, 10);
	len = ft_print_string(flags, num_str, 'u');
	free(num_str);
	return (len);
}

int				ft_print_hex(t_flag flags, unsigned int value, int type)
{
	int		len;
	char	*num_str;
	int		i;

	flags = define_flags(flags, 0);
	if (flags.dot && (value == 0) && (flags.precision == 0))
		num_str = ft_strdup("");
	else
		num_str = ft_itoa_base_precision(value, flags.precision, 16);
	i = 0;
	if (type == 1)
		while (num_str[i])
		{
			num_str[i] = ft_toupper(num_str[i]);
			i++;
		}
	len = ft_print_string(flags, num_str, 'x');
	free(num_str);
	return (len);
}
