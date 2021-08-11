#include "../push_swap.h"

static t_optActions init_operations()
{
	t_optActions operations;
	
	operations.ra = 0;
	operations.rb = 0;
	operations.rra = 0;
	operations.rrb = 0;
	operations.rr = 0;
	operations.rrr = 0;
	operations.total = 2147483647;
	return (operations);
}

static t_optActions	fill_case_one(t_optActions current_operations, int case_one)
{
	t_optActions	operations;
	
	operations = init_operations();
	operations.total = case_one;
	if (case_one == current_operations.ra)
	{
		operations.rr = current_operations.rb;
		operations.ra = current_operations.ra - current_operations.rb;
	}
	else
	{
		operations.rr = current_operations.ra;
		operations.rb = current_operations.rb - current_operations.ra;
	}
	return (operations);
}

static t_optActions	fill_case_two(t_optActions current_operations, int case_two)
{
	t_optActions	operations;
	
	operations = init_operations();
	operations.total = case_two;
	if (case_two == -current_operations.rra)
	{
		operations.rrr = -current_operations.rrb;
		operations.rra = -(current_operations.rra - current_operations.rrb);
	}
	else
	{
		operations.rrr = -current_operations.rra;
		operations.rrb = -(current_operations.rrb - current_operations.rra);
	}
	return (operations);
}

static t_optActions	fill_case_three(t_optActions current_operations, int case_three)
{
	t_optActions	operations;
	
	operations = init_operations();
	operations.total = case_three;
	operations.ra = current_operations.ra;
	operations.rrb = -current_operations.rrb;
	return (operations);
}

static t_optActions	fill_case_four(t_optActions current_operations, int case_four)
{
	t_optActions	operations;
	
	operations = init_operations();
	operations.total = case_four;
	operations.rb = current_operations.rb;
	operations.rra = -current_operations.rra;
	return (operations);
}

static void	find_count_operations(t_optActions *operations)
{
	int				case_one;
	int				case_two;
	int				case_three;
	int				case_four;
	
	case_one = ft_max((*operations).ra, (*operations).rb);
	case_two = ft_max(-(*operations).rra, -(*operations).rrb);
	case_three = (*operations).ra - (*operations).rrb;
	case_four = (*operations).rb - (*operations).rra;
	if (case_one < (*operations).total && case_one <= case_two && case_one <= case_three && case_one <= case_four)
		*operations = fill_case_one(*operations, case_one);
	else if (case_two < (*operations).total && case_two < case_one && case_two <= case_three && case_two <= case_four)
		*operations = fill_case_two(*operations, case_two);
	else if (case_three < (*operations).total && case_three < case_one && case_three < case_two && case_three <= case_four)
		*operations = fill_case_three(*operations, case_three);
	else if (case_four < (*operations).total && case_four < case_one && case_four < case_two && case_four < case_three)
		*operations = fill_case_four(*operations, case_four);
}

void	find_markup_elem(DblLinkedList *stack, Node *head_A, size_t *next_keep_in_stack, size_t *prev_keep_in_stack)
{
	Node	*tmp_next;
	Node	*tmp_prev;
	
	tmp_next = head_A->next;
	if (!head_A->next)
		tmp_next = stack->head;
	while (tmp_next && tmp_next->data.keep_in_stack != 1)
		tmp_next = tmp_next->next;
	*next_keep_in_stack = tmp_next->data.index;
	tmp_prev = head_A->prev;
	if (!head_A->prev)
		tmp_prev = stack->tail;
	while (tmp_prev && tmp_prev->data.keep_in_stack != 1)
		tmp_prev = tmp_prev->prev;
	*prev_keep_in_stack = tmp_prev->data.index;
}

static void find_count_rotate_stackA(DblLinkedList *stack, Node *head_A, Node *head_B, t_optActions *current_operations)
{
	size_t			currentA;
	size_t 			currentB;
	size_t			next_keep_in_stack;
	size_t			prev_keep_in_stack;
	
	find_markup_elem(stack, head_A, &next_keep_in_stack, &prev_keep_in_stack);
	currentA = head_A->data.index;
	currentB = head_B->data.index;
	*current_operations = init_operations();
	if (!check_indexA(currentB, prev_keep_in_stack, currentA))
	{
		while (!check_indexA(currentB, currentA, next_keep_in_stack) && head_A->next)
		{
			head_A = head_A->next;
			if (head_A->data.keep_in_stack == 1)
			{
				find_markup_elem(stack, head_A, &next_keep_in_stack, &prev_keep_in_stack);
				prev_keep_in_stack = currentA;
				currentA = head_A->data.index;
			}
		}
		(*current_operations).ra = (int)head_A->data.pos_in_stack + 1;
		while (head_A->next->data.index != next_keep_in_stack && head_A->next)
		    head_A = head_A->next;
		(*current_operations).rra = (int)head_A->data.pos_in_stack - stack->size + 1;
	}
}

t_optActions	find_min_count_actions(DblLinkedList *stackA, DblLinkedList *stackB)
{
	size_t			i;
	t_optActions	operations;
	t_optActions	current_operations;
	Node			*tmp_head_A;
	Node			*tmp_head_B;

    tmp_head_B = stackB->head;
    current_operations = init_operations();

    operations.total = 2147483647;
	i = 0;
	while ((int)i < (int)stackB->size)
	{
		tmp_head_A = stackA->head;
		find_count_rotate_stackA(stackA, tmp_head_A, tmp_head_B, &current_operations);
		current_operations.rb = (int)i;
		current_operations.rrb = (int)(i - stackB->size);
		find_count_operations(&current_operations);
		if (current_operations.total < operations.total)
			operations = current_operations;
		tmp_head_B = tmp_head_B->next;
		i++;
	}
	return (operations);
}
