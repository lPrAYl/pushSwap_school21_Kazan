#include "../push_swap.h"

static size_t	check_unsort_elm(t_List *stk)
{
	t_Node	*tmp;
	size_t	count;

	count = 0;
	tmp = stk->head;
	while (tmp && tmp->data.keep_in_stk == 1)
	{
		count++;
		tmp = tmp->next;
	}
	if (count == stk->size)
		count = 0;
	return (count);
}

static void	do_actions(t_List **stkA, t_List **stkB, t_opt actions)
{
	while (actions.ra-- > 0)
		rotate(stkA, stkB, 'a', 'w');
	while (actions.rb-- > 0)
		rotate(stkA, stkB, 'b', 'w');
	while (actions.rra-- > 0)
		rev_rotate(stkA, stkB, 'a', 'w');
	while (actions.rrb-- > 0)
		rev_rotate(stkA, stkB, 'b', 'w');
	while (actions.rr-- > 0)
		rotate(stkA, stkB, 's', 'w');
	while (actions.rrr-- > 0)
		rev_rotate(stkA, stkB, 's', 'w');
	if ((*stkB)->size > 0)
	{
		(*stkB)->head->data.keep_in_stk = 1;
		push(stkA, stkB, 'a', 'w');
	}
}

static void	last_actions(t_List *stkA, t_List *stkB)
{
	size_t			pos;
	t_opt			actions;

	if (stkB->size == 0)
	{
		pos = stkA->head->data.index;
		if (pos < stkA->size / 2 + 1)
			while (pos--)
				rev_rotate(&stkA, &stkB, 'a', 'w');
		else
			while (pos++ < stkA->size)
				rotate(&stkA, &stkB, 'a', 'w');
		exit(EXIT_SUCCESS);
	}
	else
	{
		actions = find_min_count_actions(stkA, stkB);
		do_actions(&stkA, &stkB, actions);
	}
}

static void	check_3_elem(t_List **stkA)
{
	if ((*stkA)->head->data.keep_in_stk == 1
		&& (*stkA)->head->data.index < (*stkA)->head->next->data.index)
	{
		(*stkA)->head->next->data.keep_in_stk = 1;
		swap(stkA, NULL, 'a', 'w');
		rotate(stkA, NULL, 'a', 'w');
	}
	else if ((*stkA)->head->data.keep_in_stk == 0)
	{
		(*stkA)->head->data.keep_in_stk = 1;
		swap(stkA, NULL, 'a', 'w');
	}
	else
	{
		(*stkA)->head->next->data.keep_in_stk = 1;
		swap(stkA, NULL, 'a', 'w');
		rev_rotate(stkA, NULL, 'a', 'w');
	}
}

void	action(t_List *stkA)
{
	t_List	*stkB;
	size_t	count_unsort_elem;

	stkB = created_list();
	while (1)
	{
		count_unsort_elem = check_unsort_elm(stkA);
		if (stkA->size == 3 && count_unsort_elem != 0)
			check_3_elem(&stkA);
		if (stkA->head->data.keep_in_stk == 1)
		{
			count_unsort_elem = check_unsort_elm(stkA);
			if (count_unsort_elem != 0)
				rotate(&stkA, &stkB, 'a', 'w');
			else
				last_actions(stkA, stkB);
		}
		else
			push(&stkA, &stkB, 'b', 'w');
	}
}
