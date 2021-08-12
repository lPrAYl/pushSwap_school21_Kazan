#include "../../push_swap.h"

static void	reverse_rotate_action(t_List **stk)
{
	size_t	size;
	t_data	data;
	t_Node	*tmp;

	size = (*stk)->size;
	if (size < 2)
		return ;
	data = deleteNth(*stk, size - 1);
	data.pos_in_stk = 0;
	tmp = (*stk)->head;
	while (tmp)
	{
		tmp->data.pos_in_stk++;
		tmp = tmp->next;
	}
	pushFront(*stk, data);
}

void	rev_rotate(t_List **stkA, t_List **stkB, char stk, char write)
{
	if (stk == 'a')
	{
		reverse_rotate_action(stkA);
		if (write == 'w')
			ft_putstr_fd("rra\n", 1);
	}
	else if (stk == 'b')
	{
		reverse_rotate_action(stkB);
		if (write == 'w')
			ft_putstr_fd("rrb\n", 1);
	}
	else if (stk == 's')
	{
		reverse_rotate_action(stkA);
		reverse_rotate_action(stkB);
		if (write == 'w')
			ft_putstr_fd("rrr\n", 1);
	}
}
