/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnasium <mavrin@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 21:04:19 by vnasium           #+#    #+#             */
/*   Updated: 2020/07/29 21:04:20 by vnasium          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		ft_print_string(t_flag flags, char *str, char type)
{
	int	len;

	if (!str)
		str = "(null)";
	if (flags.precision == 0 && flags.dot && type == 's')
		str = "";
	len = (int)ft_strlen(str);
	if (flags.dot && len > flags.precision && type == 's'
		&& flags.precision > 0)
		len = flags.precision;
	return (flags.minus == 1 ?
			ft_putnstr(str, len) + ft_print_width(flags.width, len, 0) :
			ft_print_width(flags.width, len, 0) + ft_putnstr(str, len));
}
