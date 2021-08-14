#include "../../push_swap.h"

static void	swap_action(t_List **stk)
{
	size_t	size;
	t_data	data;

	size = (*stk)->size;
	if (size < 2)
		return ;
	(*stk)->head->data.pos_in_stk++;
	data = deleteNth(*stk, 1);
	data.pos_in_stk--;
	pushFront(*stk, data);
}

void	swap(t_List **stkA, t_List **stkB, char stk, char write)
{
	if (stk == 'a')
	{
		swap_action(stkA);
		if (write == 'w')
			ft_putstr_fd("sa\n", 1);
	}
	else if (stk == 'b')
	{
		swap_action(stkB);
		if (write == 'w')
			ft_putstr_fd("sb\n", 1);
	}
	else if (stk == 's')
	{
		swap_action(stkA);
		swap_action(stkB);
		if (write == 'w')
			ft_putstr_fd("ss\n", 1);
	}
}
