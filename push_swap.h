#ifndef PUSH_SWAP_H
#define PUSH_SWAP_H

# include "./libft/libft.h"

typedef struct	s_compare
{
	size_t	pos_min;
	int 	min;
	size_t	pos_max;
	int 	max;
}				t_compare;

typedef struct  s_data
{
	int 	value;
	size_t	pos_in_stack;
	size_t	index;
	int		keep_in_stack;
}               t_data;

typedef struct	s_position
{
	size_t 	index_begin;
	size_t	step;
	size_t	count_elem;
}				t_position;

typedef struct  Node
{
	struct s_data	data;
	struct Node		*next;
	struct Node		*prev;
}               Node;

typedef	struct	DblLinkedList
{
	size_t		size;
	struct Node	*head;
	struct Node	*tail;
}				DblLinkedList;

typedef struct	Ring
{
	size_t	size;
	Node	*current;
}				Ring;

DblLinkedList	*createDblLinkedList();
void			deleteDblLinkedList(DblLinkedList **list);
void			pushFront(DblLinkedList *list, struct s_data data);
struct s_data	popFront(DblLinkedList *list);
void			pushBack(DblLinkedList *list, struct s_data data);
struct s_data	popBack(DblLinkedList *list);
Node			*getNth(DblLinkedList *list, size_t index);
Node			*getNthq(DblLinkedList *list, size_t index);
void			insert(DblLinkedList *list, size_t index, struct s_data data);
struct s_data	deleteNth(DblLinkedList *list, size_t index);
void			printInt(struct s_data data);
void			printDblLinkedList(DblLinkedList *list);
DblLinkedList	*fromArray(void *arr, size_t n, size_t size);



void 			ft_check_chunk(char *s);
DblLinkedList	*ft_validate_data(char **argv);
t_position		markup_stack(DblLinkedList *stack);

void			operation(DblLinkedList *stackA, t_position *best_stack);

void			ft_error(char *s);

#endif
