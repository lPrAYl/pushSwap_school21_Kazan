NAME = libftprintf.a

SRCS =	ft_printf.c			ft_parsing.c			ft_printing_chars.c\
		ft_printf_utils.c	ft_printing_number.c	ft_printing_pointer.c\
		ft_printf_utils_2.c

OBJS = $(patsubst %.c, %.o, $(SRCS))

FLAGS = -Wall -Werror -Wextra

HEADER = ft_printf.h

all : $(NAME)

$(NAME) : $(OBJS) 
	@ar rcs $@ $?

%.o : %.c $(HEADER)
	@gcc $(FLAGS) -c $< -o $@

clean :
	@rm -f $(OBJS)

fclean : clean
	@rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re