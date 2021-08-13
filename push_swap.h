#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "./libft/libft.h"

typedef struct s_data
{
	int		value;
	size_t	pos_in_stk;
	size_t	index;
	int		keep_in_stk;
}				t_data;

typedef struct s_Node
{
	t_data			data;
	struct s_Node	*next;
	struct s_Node	*prev;
}				t_Node;

typedef struct s_compare
{
	size_t	pos_min;
	int		min;
	size_t	pos_max;
	int		max;
}				t_compare;

typedef struct s_List
{
	size_t	size;
	t_Node	*head;
	t_Node	*tail;
}				t_List;

typedef struct s_best
{
	size_t	tailInd;
	size_t	prevInd;
	size_t	lenght;
	size_t  len;
	size_t	iteration;
	t_List	*stk;
}				t_best;

typedef struct s_opt
{
	int	ra;
	int	rb;
	int	rra;
	int	rrb;
	int	rr;
	int	rrr;
	int	total;
}			t_opt;

/**************** Functions for a doubly linked list ****************/

t_List	*created_list(void);
void	delete_List(t_List **list);
void	pushFront(t_List *list, struct s_data data);
t_data	popFront(t_List *list);
void	pushBack(t_List *list, struct s_data data);
t_data	popBack(t_List *list);
t_Node	*getNthq(t_List *list, size_t index);
void	insert(t_List *list, size_t index, struct s_data data);
t_data	deleteNth(t_List *list, size_t index);
void	print_List(t_List *list);

/************************ Prepare functions ************************/

t_List	*validate_data(char **argv);
void	check_dup_and_index(t_List *stkack, size_t index);
void	markup_stack(t_List *stkack);
t_opt	ind_min_count_actions(t_List *stkackA, t_List *stkackB);
t_opt	init_actions(void);
void	action(t_List *stkackA);
void	find_count_actions(t_opt *actions);
t_opt	find_min_count_actions(t_List *stkA, t_List *stkB);
void	incrSubseq(t_List *stk, t_best **subseq, t_Node *cur, size_t i);
int		check_indexA(size_t index, size_t prev, size_t next);
void	markup_elem(t_List *stk, t_Node *hdA, size_t *nk, size_t *pk);

/********************** Functions for actions **********************/

void	swap(t_List **stkA, t_List **stkB, char st, char w);
void	rotate(t_List **stkA, t_List **stkB, char st, char w);
void	rev_rotate(t_List **stkA, t_List **stkB, char st, char w);
void	push(t_List **stkA, t_List **stkB, char stkack, char w);

#endif
