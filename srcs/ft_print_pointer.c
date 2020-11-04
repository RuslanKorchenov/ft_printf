/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_pointer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnasium <mavrin@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 21:04:10 by vnasium           #+#    #+#             */
/*   Updated: 2020/07/29 21:04:11 by vnasium          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		ft_print_pointer(t_flag flags, unsigned long long value)
{
	char	*str;
	int		len;

	if (flags.zero && (flags.dot || flags.minus))
		flags.zero = 0;
	if (flags.zero)
	{
		flags.precision = flags.width - 2;
		flags.width = 0;
	}
	if (flags.dot && flags.precision == 0 && value == 0)
		str = ft_strdup("0x");
	else
		str = ft_ptoa_precision(value, flags.precision);
	len = ft_print_string(flags, str, 'p');
	free(str);
	return (len);
}
