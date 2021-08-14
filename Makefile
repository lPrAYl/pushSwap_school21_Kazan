NAME			=	push_swap

CHECKER			= 	checker

CC				=	gcc

FLAGS			=	-Wall -Wextra -Werror -g

SOURCES			=	push_swap.c		operation.c		validation.c	indexing.c	markup.c 			\
					search_subsequence.c	find_min_actions.c	find_min_actions_utils.c			\
					actions/swap.c	actions/push.c	actions/rotate.c	actions/reverse_rotate.c	\
					list_utils.c	list_utils2.c

CHECKER_SOURCES	=	checker.c		validation.c	indexing.c										\
					actions/swap.c	actions/push.c	actions/rotate.c	actions/reverse_rotate.c	\
					list_utils.c	list_utils2.c

SRCDIR			=	./srcs/

CHECKERDIR		=	./bonus/

SRC				=	$(addprefix $(SRCDIR), $(SOURCES))

CHECKER_SRC		=	$(addprefix $(CHECKERDIR), $(CHECKER_SOURCES))

HEADER			=	push_swap.h

HEADER_CHECKER	=	./bonus/checker.h

OBJECTS			=	$(SRC:.c=.o)

CHECKER_OBJECTS	=	$(CHECKER_SRC:.c=.o)

LIBFT			=	./libft/libft.a

LIBFLAGS		=	-L ./libft -lft

all				:	$(NAME)

bonus			:	$(CHECKER)

$(LIBFT)		:
					@$(MAKE) -C ./libft/

$(NAME)			:	$(HEADER) $(LIBFT) $(OBJECTS)
					@$(CC) $(FLAGS) $(OBJECTS) $(LIBFLAGS) -o $(NAME)
					@echo "project created / updated"

$(CHECKER)		:	$(HEADER_CHECKER) $(LIBFT) $(CHECKER_OBJECTS)
					@$(CC) $(FLAGS) $(CHECKER_OBJECTS) $(LIBFLAGS) -o $(CHECKER)
					@echo "checker created"

%.o				:	%.c $(HEADER)
					@$(CC) $(FLAGS) -c $< -o $@

clean			:
					@rm -rf $(OBJECTS) $(CHECKER_OBJECTS)
					@$(MAKE) clean -C ./libft/
					@echo "project clean done"

fclean			:
					@rm -rf $(OBJECTS) $(CHECKER_OBJECTS) $(NAME) $(CHECKER)
					@$(MAKE) fclean -C ./libft/
					@echo "project fclean done"

re				:	fclean all

norm			:
					norminette $(shell find *.c *.h)

.PHONY			:	all bonus clean fclean re norm
