NAME			=	push_swap

CC				=	gcc

FLAGS			=	-Wall -Wextra -Werror -g

SOURCES			=	push_swap.c		validation.c	indexing.c	markup.c	actions/swap.c actions/rotate.c	\
					actions/reverse_rotate.c	operation.c	operations_utils.c	dbl_linked_list_utils.c\
					ring_utils.c

SRCDIR			=	./srcs/

SRC				=	$(addprefix $(SRCDIR), $(SOURCES))

HEADER			=	push_swap.h

OBJECTS			=	$(SRC:.c=.o)

LIBFT			=	./libft/libft.a

LIBFLAGS		=	-L ./libft -lft

all				:	$(NAME)

$(LIBFT)		:
					@$(MAKE) -C ./libft/

$(NAME)			:	$(HEADER) $(LIBFT) $(OBJECTS)
					@$(CC) $(FLAGS) $(OBJECTS) $(LIBFLAGS) -o $(NAME)
					@echo "project created / updated"
					 bash ~/.clean

%.o				:	%.c $(HEADER)
					@$(CC) $(FLAGS) -c $< -o $@

clean			:
					rm -rf $(OBJECTS)
					@$(MAKE) clean -C ./libft/
					@echo "project clean done"

fclean			:
					@rm -rf $(OBJECTS) $(NAME)
					@$(MAKE) fclean -C ./libft/
					@echo "project fclean done"

re				:	fclean all

norm			:
					norminette $(shell find *.c *.h)

.PHONY			:	all bonus clean fclean re norm
