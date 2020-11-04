/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_percent.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnasium <mavrin@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 21:05:16 by vnasium           #+#    #+#             */
/*   Updated: 2020/07/29 21:05:17 by vnasium          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		ft_print_percent(t_flag flags)
{
	int	len;

	len = 0;
	if (flags.minus)
	{
		ft_putchar('%');
		len += ft_print_width(flags.width, 1, 0);
	}
	else
	{
		if (flags.zero)
			len += ft_print_width(flags.width, 1, 1);
		else
			len += ft_print_width(flags.width, 1, 0);
		ft_putchar('%');
	}
	return (len + 1);
}
