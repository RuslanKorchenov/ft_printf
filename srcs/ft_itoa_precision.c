/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_precision.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnasium <mavrin@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 21:03:33 by vnasium           #+#    #+#             */
/*   Updated: 2020/07/29 21:03:34 by vnasium          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static	int	check_negative(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

static	int	get_len(int n, int precision)
{
	int	len;

	len = 1;
	while (n / 10 != 0)
	{
		n /= 10;
		len++;
	}
	return (precision > len ? precision : len);
}

char		*ft_itoa_precision(int n, int precision)
{
	int		len;
	char	*str;
	int		i;

	i = 0;
	len = get_len(n, precision);
	if (n < 0)
		len++;
	if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (i < len)
		str[i++] = '0';
	if (n < 0)
		str[0] = '-';
	str[len] = '\0';
	while (n / 10 != 0)
	{
		str[--len] = check_negative(n % 10) + '0';
		n /= 10;
	}
	str[--len] = check_negative(n % 10) + '0';
	return (str);
}
