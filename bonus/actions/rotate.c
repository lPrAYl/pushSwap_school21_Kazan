#include "../../push_swap.h"

static void	rotate_action(t_List **stk)
{
	size_t	size;
	t_data	data;
	t_Node	*tmp;

	size = (*stk)->size;
	if (size < 2)
		return ;
	data = popFront(*stk);
	data.pos_in_stk = size - 1;
	tmp = (*stk)->head;
	while (tmp)
	{
		tmp->data.pos_in_stk--;
		tmp = tmp->next;
	}
	pushBack(*stk, data);
}

void	rotate(t_List **stkA, t_List **stkB, char stk, char write)
{
	if (stk == 'a')
	{
		rotate_action(stkA);
		if (write == 'w')
			ft_putstr_fd("ra\n", 1);
	}
	else if (stk == 'b')
	{
		rotate_action(stkB);
		if (write == 'w')
			ft_putstr_fd("rb\n", 1);
	}
	else if (stk == 's')
	{
		rotate_action(stkA);
		rotate_action(stkB);
		if (write == 'w')
			ft_putstr_fd("rr\n", 1);
	}
}
