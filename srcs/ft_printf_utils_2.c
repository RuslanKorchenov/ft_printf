/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnasium <mavrin@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 21:04:50 by vnasium           #+#    #+#             */
/*   Updated: 2020/07/29 21:04:51 by vnasium          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		ft_print_width(int width, int extra, int zero)
{
	int	len;

	len = 0;
	while (width - extra > 0)
	{
		if (zero)
			ft_putchar('0');
		else
			ft_putchar(' ');
		len++;
		width--;
	}
	return (len);
}

int		ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		c -= 32;
	return (c);
}
