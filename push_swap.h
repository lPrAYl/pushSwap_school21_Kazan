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

typedef struct	s_best
{
	size_t 	tailIndexes;
	size_t 	prevIndexes;
	size_t	lenght;
	size_t	iteration;
	DblLinkedList *stack;
}				t_best;

typedef struct	Ring
{
	size_t	size;
	Node	*current;
}				Ring;

typedef struct  s_optActions
{
    int ra;
    int rb;
    int rra;
    int rrb;
    int rr;
    int rrr;
    int total;
}               t_optActions;

/********************* Functions for a doubly linked list *********************/

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


void			ft_error(char *s);
void	        find_markup_elem(DblLinkedList *stack, Node *head_A, size_t *next_keep_in_stack, size_t *prev_keep_in_stack);
void			check_dup_and_index(DblLinkedList *stack);
DblLinkedList	*ft_validate_data(char **argv);
void			markup_stack(DblLinkedList *stack);

t_optActions	find_min_count_actions(DblLinkedList *stackA, DblLinkedList *stackB);
int             check_indexA(size_t index, size_t prev, size_t next);

void			swap(DblLinkedList **stackA, DblLinkedList **stackB, char stack, char write);
void			rotate(DblLinkedList **stackA, DblLinkedList **stackB, char stack, char write);
void			reverse_rotate(DblLinkedList **stackA, DblLinkedList **stackB, char stack, char write);
void	        push(DblLinkedList **stackA, DblLinkedList **stackB, char stack, char write);


void			sa(DblLinkedList **stackA);
void			sb(DblLinkedList **stackB);
void			ss(DblLinkedList **stackA, DblLinkedList **stackB);
void			pa(DblLinkedList **stackA, DblLinkedList **stackB);
void			pb(DblLinkedList **stackA, DblLinkedList **stackB);
void			ra(DblLinkedList **stackA);
void			rb(DblLinkedList **stackB);
void			rr(DblLinkedList **stackA, DblLinkedList **stackB);
void			rra(DblLinkedList **stackA);
void			rrb(DblLinkedList **stackB);
void			rrr(DblLinkedList **stackA, DblLinkedList **stackB);

void			operation(DblLinkedList *stackA);

#endif
