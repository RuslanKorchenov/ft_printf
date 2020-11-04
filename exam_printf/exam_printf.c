#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>

typedef	struct	s_flag
{
	int	dot;
	int	width;
	int	precision;
}				t_flag;

t_flag init_flags(t_flag flags)
{
	flags.dot = 0;
	flags.width = 0;
	flags.precision = 0;
	return (flags);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(const char *str)
{
	char			*s;
	unsigned int	i;

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

int		ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int		ft_checkflag(char c)
{
	char	*flags;

	flags = "0.123456789";
	while (*flags)
		if (*flags++ == c)
			return (1);
	return (0);
}

int		ft_putchar(int c)
{
	write(1, &c, 1);
	return (1);
}

t_flag		parse_flags(const char *format, va_list ap, t_flag flags)
{
	int i;

	i = 0;
	while (format[i] && ft_checkflag(format[i]))
	{
		if (ft_isdigit(format[i]) && flags.dot == 0)
			flags.width = (flags.width * 10) + (format[i] - '0');
		else if (format[i] == '.')
			flags.dot = 1;
		else if (ft_isdigit(format[i]) && flags.dot == 1)
			flags.precision = (flags.precision * 10) + (format[i] - '0');
		i++;
	}
	return (flags);
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

int		ft_print_width(int width, int extra)
{
	int	len;

	len = 0;
	while (width - extra > 0)
	{
		ft_putchar(' ');
		len++;
		width--;
	}
	return (len);
}

int		ft_print_string(t_flag flags, char *str)
{
	int	len;

	if (!str)
		str = "(null)";
	if (flags.precision == 0 && flags.dot)
		str = "";
	len = (int)ft_strlen(str);
	if (flags.dot && len > flags.precision && flags.precision > 0)
		len = flags.precision;
	return (ft_print_width(flags.width, len) + ft_putnstr(str, len));
}

static	int	check_negative(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

static	int	get_len(int n, int precision, int base)
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

char		*ft_itoa_base_precision(int n, int precision, int base)
{
	int		len;
	char	*str;
	int		i;

	i = 0;
	len = get_len(n, precision, base);
	if (n < 0)
		len++;
	if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (i < len)
		str[i++] = '0';
	if (base == 10 && n < 0)
		str[0] = '-';
	if (base == 16)
		str[1] = 'x';
	str[len] = '\0';
	while (n / base != 0)
	{
		str[--len] = "0123456789abcdef"[check_negative(n % base)];
		n /= base;
	}
	str[--len] = "0123456789abcdef"[check_negative(n % base)];
	return (str);
}

int				ft_print_int(t_flag flags, int value)
{
	int		len;
	char	*num_str;


	if (flags.dot && value == 0 && flags.precision == 0)
		num_str = ft_strdup("");
	else
		num_str = ft_itoa_base_precision(value, flags.precision, 10);
	len = ft_strlen(num_str);
	len = ft_print_width(flags.width, len) + ft_putnstr(num_str, len);
	free(num_str);
	return (len);
}

int				ft_print_hex(t_flag flags, unsigned int value, int type)
{
	int		len;
	char	*num_str;
	int		i;

	if (flags.dot && value == 0 && flags.precision == 0)
		num_str = ft_strdup("");
	else
		num_str = ft_itoa_base_precision(value, flags.precision, 16);
	i = 0;
	len = ft_strlen(num_str);
	len = ft_print_width(flags.width, len) + ft_putnstr(num_str, len);
	free(num_str);
	return (len);
}

int		ft_print(char type, t_flag flags, va_list ap)
{
	int len;

	len = 0;
	if (type == 's')
		len = ft_print_string(flags, va_arg(ap, char *));
	else if (type == 'd')
		len = ft_print_int(flags, va_arg(ap, int));
	else if (type == 'x')
		len = ft_print_hex(flags, va_arg(ap, unsigned int), 0);
	return (len);
}

int		ft_printf(const char *format, ...)
{
	va_list		ap;
	int			len;
	int			i;
	t_flag		flags;
	
	i = 0;
	len = 0;
	va_start(ap, format);
	while(format[i] != '\0')
	{
		if (format[i] == '%' && format[i + 1] != '\0')
		{
			flags = init_flags(flags);
			flags = parse_flags(&format[++i], ap, flags);
			while (ft_checkflag(format[i]))
				i++;
			len += ft_print(format[i], flags, ap);
		}
		else if (format[i] != '%')
			len += ft_putchar(format[i]);
		i++;
	}
	va_end(ap);
	return (len);
}
