#include "../push_swap.h"

t_opt	init_actions(void)
{
	t_opt	actions;

	actions.ra = 0;
	actions.rb = 0;
	actions.rra = 0;
	actions.rrb = 0;
	actions.rr = 0;
	actions.rrr = 0;
	actions.total = 2147483647;
	return (actions);
}

void	markup_elem(t_List *stk, t_Node *hdA, size_t *nk, size_t *pk)
{
	t_Node	*tmp_next;
	t_Node	*tmp_prev;

	tmp_next = hdA->next;
	if (!hdA->next)
		tmp_next = stk->head;
	while (tmp_next->next && tmp_next->data.keep_in_stk != 1)
		tmp_next = tmp_next->next;
	*nk = tmp_next->data.index;
	tmp_prev = hdA->prev;
	if (!hdA->prev)
		tmp_prev = stk->tail;
	while (tmp_prev->prev && tmp_prev->data.keep_in_stk != 1)
		tmp_prev = tmp_prev->prev;
	*pk = tmp_prev->data.index;
}

int	check_indexA(size_t index, size_t prev, size_t next)
{
	if (index > prev && index < next)
		return (1);
	else if (index < next && index < prev && prev > next)
		return (1);
	else if (index > next && index > prev && prev > next)
		return (1);
	return (0);
}

static void	rotate_stkA(t_List *stk, t_Node *hdA, t_Node *hdB, t_opt *cur_act)
{
	size_t	currentA;
	size_t	currentB;
	size_t	nk_in_stk;
	size_t	pk_in_stk;

	markup_elem(stk, hdA, &nk_in_stk, &pk_in_stk);
	currentA = hdA->data.index;
	currentB = hdB->data.index;
	*cur_act = init_actions();
	if (!check_indexA(currentB, pk_in_stk, currentA))
	{
		while (!check_indexA(currentB, currentA, nk_in_stk) && hdA->next)
		{
			hdA = hdA->next;
			if (hdA->data.keep_in_stk == 1)
			{
				currentA = hdA->data.index;
				markup_elem(stk, hdA, &nk_in_stk, &pk_in_stk);
			}
		}
		(*cur_act).ra = (int) hdA->data.pos_in_stk + 1;
		while (hdA->data.index != nk_in_stk && hdA->next)
			hdA = hdA->next;
		(*cur_act).rra = (int)(hdA->data.pos_in_stk - stk->size);
	}
}

t_opt	find_min_count_actions(t_List *stkA, t_List *stkB)
{
	size_t	i;
	t_opt	actions;
	t_opt	cur_act;
	t_Node	*tmp_hdA;
	t_Node	*tmp_hdB;

	tmp_hdB = stkB->head;
	cur_act = init_actions();
	actions.total = 2147483647;
	i = 0;
	while ((int)i < (int)stkB->size)
	{
		tmp_hdA = stkA->head;
		rotate_stkA(stkA, tmp_hdA, tmp_hdB, &cur_act);
		cur_act.rb = (int)i;
		cur_act.rrb = (int)(i - stkB->size);
		find_count_actions(&cur_act);
		if (cur_act.total < actions.total)
			actions = cur_act;
		tmp_hdB = tmp_hdB->next;
		i++;
	}
	return (actions);
}
