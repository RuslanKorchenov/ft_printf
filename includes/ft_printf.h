/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnasium <mavrin@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 13:50:54 by vnasium           #+#    #+#             */
/*   Updated: 2020/07/26 13:50:55 by vnasium          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

typedef	struct	s_flag
{
	int	zero;
	int	minus;
	int	dot;
	int	width;
	int	precision;
}				t_flag;

int				ft_printf(const char *format, ...);
int				ft_putchar(int c);
int				ft_checkflag(char c);
int				ft_isdigit(int c);
int				ft_print_width(int width, int extra, int zero);
size_t			ft_strlen(const char *str);
int				ft_putnstr(char *str, int len);
char			*ft_itoa_precision(int n, int precision);
char			*ft_strdup(const char *str);
int				ft_toupper(int c);
char			*ft_itoa_base_precision(unsigned int n, int precision,
					int base);
char			*ft_ptoa_precision(unsigned long long n, int precision);

int				ft_print_pointer(t_flag flags, unsigned long long value);
int				ft_print_char(t_flag flags, char c);
int				ft_print_string(t_flag flags, char *str, char type);
int				ft_print_hex(t_flag flags, unsigned int value, int type);
int				ft_print_unsigned(t_flag flags, unsigned int value);
int				ft_print_int(t_flag flags, int value);
int				ft_print_percent(t_flag flags);
#endif
