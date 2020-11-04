/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnasium <mavrin@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 21:03:41 by vnasium           #+#    #+#             */
/*   Updated: 2020/07/29 21:03:42 by vnasium          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		ft_print_char(t_flag flags, char c)
{
	int	len;

	len = 0;
	if (flags.minus == 1)
		ft_putchar(c);
	len = ft_print_width(flags.width, 1, 0);
	if (flags.minus == 0)
		ft_putchar(c);
	return (len + 1);
}
