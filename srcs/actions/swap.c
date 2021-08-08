#include "../../push_swap.h"

static void	swap_action(DblLinkedList **stack)
{
	size_t	size;
	t_data	data;
	
	size = (*stack)->size;
	if (size < 2)
		return ;
	(*stack)->head->data.pos_in_stack++;
	data = deleteNth(*stack, 1);
	data.pos_in_stack--;
	pushFront(*stack, data);
}

void	swap(DblLinkedList **stackA, DblLinkedList **stackB, char stack, char write)
{
	if (stack == 'a')
	{
		swap_action(stackA);
		if (write == 'w')
			ft_putstr_fd("sa\n", 1);
	}
	else if (stack == 'b')
	{
		swap_action(stackB);
		if (write == 'w')
			ft_putstr_fd("sb\n", 1);
	}
	else if (stack == 's')
	{
		swap_action(stackA);
		swap_action(stackB);
		if (write == 'w')
			ft_putstr_fd("ss\n", 1);
	}
}