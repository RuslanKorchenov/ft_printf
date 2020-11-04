/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnasium <mavrin@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 21:04:42 by vnasium           #+#    #+#             */
/*   Updated: 2020/07/29 21:04:43 by vnasium          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int		ft_putchar(int c)
{
	write(1, &c, 1);
	return (1);
}

int		ft_putnstr(char *str, int len)
{
	int	cnt;

	cnt = 0;
	while (*str && len--)
	{
		ft_putchar(*str++);
		cnt++;
	}
	return (cnt);
}

int		ft_checkflag(char c)
{
	char	*flags;

	flags = "-0.*123456789";
	while (*flags)
		if (*flags++ == c)
			return (1);
	return (0);
}
