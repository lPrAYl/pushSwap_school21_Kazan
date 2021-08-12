NAME		=	libft.a

CC			=	gcc

FLAGS		=	-Wall -Wextra -Werror

SRCS		=		ft_atoi.c		ft_bzero.c		ft_calloc.c		ft_isascii.c		\
					ft_isalnum.c	ft_isalpha.c	ft_isdigit.c	ft_isprint.c		\
					ft_itoa.c		ft_memchr.c		ft_memcmp.c		ft_memcpy.c			\
					ft_memmove.c	ft_memset.c		ft_putchar_fd.c	ft_putendl_fd.c		\
					ft_putnbr_fd.c	ft_putstr_fd.c	ft_split.c		ft_strchr.c			\
					ft_strcmp.c		ft_strdup.c		ft_strjoin.c	ft_strlcat.c		\
					ft_strlcpy.c	ft_strlen.c		ft_strmapi.c	ft_strncmp.c		\
					ft_strnstr.c	ft_strrchr.c	ft_strtrim.c	ft_substr.c			\
					ft_tolower.c	ft_toupper.c	ft_abs.c		ft_error.c

BONUS_SRCS		=	ft_lstclear.c	ft_lstfind.c	ft_lstiter.c	ft_lstadd_back.c	\
					ft_lstlast.c	ft_lstmap.c		ft_lstnew.c		ft_lstadd_front.c	\
					ft_lstsize.c	ft_lstdelone.c	 									\
					ft_isspace.c	ft_memory.c		ft_memory_utils.c					\
					deque.c			deque_utils.c	binary_search.c	ft_sort.c			\
					ft_minmax.c		ft_sqrt.c											\
					get_next_line.c	get_next_line_utils.c	get_next_line_sub.c			\

HEADER			=	libft.h			get_next_line.h

OBJECTS			=	$(SRCS:.c=.o)

BONUS_OBJECTS	=	$(BONUS_SRCS:.c=.o)

LIB_PRINTF		=	./printf/libftprintf.a

PRINTF_FLAGS	=	-L ./printf -lft

all				:	$(NAME)

bonus			:	$(HEADER) $(BONUS_OBJECTS)
					@$(MAKE) -C ./printf
					@cp $(LIB_PRINTF) $(NAME)
					@ar rcs $(NAME) $(BONUS_OBJECTS)
					@echo "libft.a created / updated"

$(NAME)			:	$(HEADER) $(OBJECTS) $(BONUS_OBJECTS)
					@$(MAKE) -C ./printf
					@cp $(LIB_PRINTF) $(NAME)
					@ar rcs $(NAME) $(OBJECTS) $(BONUS_OBJECTS)
					@echo "libft.a created / updated"

%.o				:	%.c $(HEADER)
					@$(CC) $(FLAGS) -c $< -o $@

clean			:
					@rm -rf $(OBJECTS) $(BONUS_OBJECTS)
					@$(MAKE) clean -C ./printf
					@echo "libft.a clean done"

fclean			:
					@rm -rf $(OBJECTS) $(BONUS_OBJECTS)
					@$(MAKE) fclean -C ./printf
					@rm -rf $(NAME)
					@echo "libft.a fclean done"

re				:	fclean all

norm			:
					norminette $(shell find *.c *.h)

.PHONY			:	all bonus clean fclean re norm
