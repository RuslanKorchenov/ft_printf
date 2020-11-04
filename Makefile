NAME = libftprintf.a

INCLUDES = includes/ft_printf.h

SRC = srcs/ft_itoa_base_precision.c srcs/ft_itoa_precision.c \
		srcs/ft_print_char.c srcs/ft_print_d_i_u.c \
		srcs/ft_print_pointer.c srcs/ft_print_string.c \
		srcs/ft_printf.c srcs/ft_printf_utils.c srcs/ft_strdup.c \
		srcs/ft_print_percent.c srcs/ft_printf_utils_2.c

OBJS = $(SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJS) $(INCLUDES)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)

%.o: $(SRC_PATH)%.c $(INCLUDES)
	gcc -Wall -Wextra -Werror -c $< -o $@

clean:
	rm -f $(OBJS)
	
fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY : all clean fclean re