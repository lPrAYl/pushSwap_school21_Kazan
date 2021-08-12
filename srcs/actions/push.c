#include "../../push_swap.h"

static void	push_action(t_List **stk_from, t_List **stk_to)
{
	t_data	data;
	t_Node	*tmp_to;
	t_Node	*tmp_from;

	if (*stk_from == NULL)
		return ;
	data = popFront(*stk_from);
	data.pos_in_stk = 0;
	tmp_to = (*stk_to)->head;
	tmp_from = (*stk_from)->head;
	while (tmp_to)
	{
		tmp_to->data.pos_in_stk++;
		tmp_to = tmp_to->next;
	}
	while (tmp_from)
	{
		tmp_from->data.pos_in_stk--;
		tmp_from = tmp_from->next;
	}
	pushFront(*stk_to, data);
}

void	push(t_List **stkA, t_List **stkB, char stk, char write)
{
	if (stk == 'a')
	{
		push_action(stkB, stkA);
		if (write == 'w')
			ft_putstr_fd("pa\n", 1);
	}
	else if (stk == 'b')
	{
		push_action(stkA, stkB);
		if (write == 'w')
			ft_putstr_fd("pb\n", 1);
	}
}
