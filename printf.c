#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

typedef	struct	s_flags
{
	int	dot;
	int width;
	int precision;
}				t_flags;

t_flags	init_flags(t_flags flags)
{
	flags.dot = 0;
	flags.precision = 0;
	flags.width = 0;
	return(flags);
}



size_t		ft_strlen(const char *str)
{
	size_t i;
	
	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(const char *str)
{
	char	*s;
	unsigned int i;

	if (!(s = malloc(sizeof(char) * (ft_strlen(str) + 1))))
		return (NULL);
	i = 0;
	while (str[i] != '\0')
	{
		s[i] = str[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

int	check_flag(char c)
{
	char *flags;

	flags = ".0123456789";
	while (*flags)
		if (*flags++ == c)
			return (1);
	return (0);
}
int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

t_flags	parse_flags(t_flags flags, const char *format)
{
	int i;

	i = 0;
	while (format[i] && check_flag(format[i]))
	{
		if (ft_isdigit(format[i]) && flags.dot == 0)
			flags.width = flags.width * 10 + (format[i] - '0');
		else if (format[i] == '.')
			flags.dot = 1;
		else if (ft_isdigit(format[i]) && flags.dot == 1)
			flags.precision = flags.precision * 10 + (format[i] - '0');
		i++;
	}

	return (flags);
}

int		ft_putnstr(char *str, int n)
{
	int i;

	i = 0;
	while (i != n && str[i])
	{
		ft_putchar(str[i]);
		i++;
	}
	return (i);
}

int		ft_print_width(int width, int extra)
{
	int len;

	len = 0;
	while (width - extra > 0)
	{
		len++;
		width--;
		ft_putchar(' ');
	}
	return (len);
}

int		ft_print_string(t_flags flags, char *str)
{
	int len;

	len = 0;
	if (!str)
		str = "(null)";
	if (flags.precision == 0 && flags.dot)
		str = "";
	len = (int)ft_strlen(str);
	if (flags.dot && len > flags.precision && flags.precision > 0)
		len = flags.precision;
	return (ft_print_width(flags.width, len) + ft_putnstr(str, len));
}

int		get_len(int value, int precision, int base)
{
	int len;

	len = 1;
	while (value / base != 0)
	{
		value /= base;
		len++;
	}
	return (precision > len ? precision : len);
}

int		check_negative(int c)
{
	if (c < 0)
		return (-c);
	return (c);
}

char	*ft_itoa_base(int value, int precision, int base)
{
	char *str;
	int i;
	int len;

	len = get_len(value, precision, base);
	if (value < 0)
		len++;
	if (!(str = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	i = 0;
	while (i < len)
		str[i++] = '0';
	if (base == 10 && value < 0)
		str[0] = '-';
	if (base == 16)
		str[1] = 'x';
	str[len] = '\0';
	while (value / base != 0)
	{
		str[--len] = "0123456789abcdef"[check_negative(value % base)];
		value /= base;
	}
	str[--len] = "0123456789abcdef"[check_negative(value % base)];
	return (str);
}

int		ft_print_int(t_flags flags, int value)
{
	int len;
	char *num_str;

	len = 0;
	if (flags.precision == 0 && flags.dot)
		num_str = ft_strdup("");
	else
		num_str = ft_itoa_base(value, flags.precision, 10);
	len = ft_strlen(num_str);
	len = ft_print_width(flags.width, len) + ft_putnstr(num_str, len);
	free(num_str);
	return (len);
}

int		ft_print_hex(t_flags flags, int value)
{
	int len;
	char *num_str;

	len = 0;
	if (flags.precision == 0 && flags.dot)
		num_str = ft_strdup("");
	else
		num_str = ft_itoa_base(value, flags.precision, 16);
	len = ft_strlen(num_str);
	len = ft_print_width(flags.width, len) + ft_putnstr(num_str, len);
	free(num_str);
	return (len);
}

int		ft_print(t_flags flags, char c, va_list ap)
{
	int len;

	len = 0;
	if (c == 's')
		len = ft_print_string(flags, va_arg(ap, char *));
	else if (c == 'd')
		len = ft_print_int(flags, va_arg(ap, int));
	else if (c == 'x')
		len = ft_print_hex(flags, va_arg(ap, unsigned int));
	return (len);
}

int		ft_printf(const char *format, ...)
{
	int len;
	int i;
	va_list ap;
	t_flags flags;

	va_start(ap, format);
	i = 0;
	len = 0;
	while (format[i] != '\0')
	{
		if (format[i] == '%' && format[i + 1] != '\0')
		{
			flags = init_flags(flags);
			flags = parse_flags(flags, &format[++i]);
			while (check_flag(format[i]))
				i++;
			len += ft_print(flags, format[i], ap);
		}
		else if (format[i] != '%')
			len += ft_putchar(format[i]);
		i++;
	}
	va_end(ap);
	return (len);
}