/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base_precision.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnasium <mavrin@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 21:03:21 by vnasium           #+#    #+#             */
/*   Updated: 2020/07/29 21:03:24 by vnasium          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static	int	get_len(unsigned int n, int precision, int base)
{
	int	len;

	len = 1;
	while (n / base != 0)
	{
		n /= base;
		len++;
	}
	return (precision > len ? precision : len);
}

static	int	get_plen(unsigned long long n, int precision)
{
	int len;

	len = 1;
	while (n / 16 != 0)
	{
		n /= 16;
		len++;
	}
	return (precision > len ? precision : len);
}

char		*ft_itoa_base_precision(unsigned int n, int precision, int base)
{
	int		len;
	char	*str;
	int		i;

	i = 0;
	if (base < 2 || base > 16)
		return (NULL);
	len = get_len(n, precision, base);
	if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (i < len)
		str[i++] = '0';
	str[len] = '\0';
	while (n / base != 0)
	{
		str[--len] = "0123456789abcdef"[n % base];
		n /= base;
	}
	str[--len] = "0123456789abcdef"[n % base];
	return (str);
}

char		*ft_ptoa_precision(unsigned long long n, int precision)
{
	int		len;
	char	*str;
	int		i;

	i = 0;
	len = get_plen(n, precision) + 2;
	if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (i < len)
		str[i++] = '0';
	str[1] = 'x';
	str[len] = '\0';
	while (n / 16 != 0)
	{
		str[--len] = "0123456789abcdef"[n % 16];
		n /= 16;
	}
	str[--len] = "0123456789abcdef"[n % 16];
	return (str);
}
