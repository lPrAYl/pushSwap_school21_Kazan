#include "../push_swap.h"

/********************* Initializing elements for comparison *********************/

static t_compare	init_sort_data(Node *current_i, size_t i)
{
	struct s_compare	sort;
	
	sort.pos_min = i;
	sort.min = current_i->data.value;
	sort.pos_max = i;
	sort.max = current_i->data.value;
	return (sort);
}

/********************* Sorting and checking for duplicates *********************/

static t_compare	comparison(DblLinkedList **stack, Node *current_i, size_t i)
{
	size_t		j;
	t_compare	sort;
	Node 		*current_j;
	
	sort = init_sort_data(current_i, i);
	j = i + 1;
	while (j < (*stack)->size)
	{
		current_j = getNthq(*stack, j);
		if (current_j->data.value < sort.min && (int)current_j->data.index == -1)
		{
			sort.min = current_j->data.value;
			sort.pos_min = j;
		}
		else if (current_j->data.value > sort.max && (int)current_j->data.index == -1)
		{
			sort.max = current_j->data.value;
			sort.pos_max = j;
		}
		else if (current_j->data.value == sort.min || current_j->data.value == sort.max)
			ft_error("Duplicate number\n");
		j++;
	}
	return (sort);
}

/********************* Arrangement of indices *********************/

void	check_dup_and_index(DblLinkedList *stack)
{
	size_t		i;
	size_t		j;
	size_t 		index;
	Node		*current_i;
	Node 		*current_j;
	t_compare	sort;
	
	i = 0;
	index = 0;
	j = stack->size - 1;
	while (i < stack->size)
	{
		current_i = getNthq(stack, i);
		current_i->data.pos_in_stack = i;
		while ((int)current_i->data.index == -1)
		{
			sort = comparison(&stack, current_i, i);
			current_j = getNthq(stack, sort.pos_min);
			current_j->data.index = index++;
			current_j = getNthq(stack, sort.pos_max);
			current_j->data.index = j--;
		}
		i++;
	}
}
