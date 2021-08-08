#include "../../push_swap.h"

static void	reverse_rotate_action(DblLinkedList **stack)
{
	size_t	size;
	t_data	data;
	Node	*tmp;
	
	size = (*stack)->size;
	if (size < 2)
		return ;
	data = deleteNth(*stack, size - 1);
	data.pos_in_stack = 0;
	tmp = (*stack)->head;
	while (tmp)
	{
		tmp->data.pos_in_stack++;
		tmp = tmp->next;
	}
	pushFront(*stack, data);
}

void	reverse_rotate(DblLinkedList **stackA, DblLinkedList **stackB, char stack, char write)
{
	if (stack == 'a')
	{
		reverse_rotate_action(stackA);
		if (write == 'w')
			ft_putstr_fd("rra\n", 1);
	}
	else if (stack == 'b')
	{
		reverse_rotate_action(stackB);
		if (write == 'w')
			ft_putstr_fd("rrb\n", 1);
	}
	else if (stack == 's')
	{
		reverse_rotate_action(stackA);
		reverse_rotate_action(stackB);
		if (write == 'w')
			ft_putstr_fd("rrr\n", 1);
	}
}