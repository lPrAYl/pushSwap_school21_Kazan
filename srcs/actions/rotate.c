#include "../../push_swap.h"

static void	rotate_action(DblLinkedList **stack)
{
	size_t	size;
	t_data	data;
	Node	*tmp;
	
	size = (*stack)->size;
	if (size < 2)
		return ;
	data = popFront(*stack);
	data.pos_in_stack = size - 1;
	tmp = (*stack)->head;
	while (tmp)
	{
		tmp->data.pos_in_stack--;
		tmp = tmp->next;
	}
	pushBack(*stack, data);
}

void	rotate(DblLinkedList **stackA, DblLinkedList **stackB, char stack, char write)
{
	if (stack == 'a')
	{
		rotate_action(stackA);
		if (write == 'w')
			ft_putstr_fd("ra\n", 1);
	}
	else if (stack == 'b')
	{
		rotate_action(stackB);
		if (write == 'w')
			ft_putstr_fd("rb\n", 1);
	}
	else if (stack == 's')
	{
		rotate_action(stackA);
		rotate_action(stackB);
		if (write == 'w')
			ft_putstr_fd("rr\n", 1);
	}
}