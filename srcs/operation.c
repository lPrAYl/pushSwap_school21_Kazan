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

void    check_elem(t_List **stkA, t_List **stkB)
{
    size_t	nk;
    size_t	pk;

    markup_elem(*stkA, (*stkA)->head, &pk, &nk);
    if ((*stkA)->head->data.keep_in_stk == 0 && (*stkA)->head->next->data.keep_in_stk == 1)
    {
        rotate(stkA, stkB, 'a', 'n');
        markup_elem(*stkA, (*stkA)->head, &pk, &nk);
        rev_rotate(stkA, stkB, 'a', 'n');
        if (check_indexA((*stkA)->head->data.index, (*stkA)->head->next->data.index, nk))
        {
            (*stkA)->head->data.keep_in_stk = 1;
            swap(stkA, stkB, 'a', 'w');
            rev_rotate(stkA, stkB, 'a', 'w');
        }
        else
            push(stkA, stkB, 'b', 'w');
    }
    else if ((*stkA)->head->data.keep_in_stk == 0 && (*stkA)->tail->data.keep_in_stk == 1)
    {
        rev_rotate(stkA, stkB, 'a', 'n');
        markup_elem(*stkA, (*stkA)->head, &pk, &nk);
        rotate(stkA, stkB, 'a', 'n');
        if (check_indexA((*stkA)->head->data.index, pk, (*stkA)->tail->data.index))
        {
            (*stkA)->head->data.keep_in_stk = 1;
            swap(stkA, stkB, 'a', 'w');
            rotate(stkA, stkB, 'a', 'w');
        }
        else
            push(stkA, stkB, 'b', 'w');
    }
    else if ((*stkA)->head->data.keep_in_stk == 1 && (*stkA)->head->next->data.keep_in_stk == 0 &&
        check_indexA((*stkA)->head->next->data.index, pk, (*stkA)->head->data.index))
    {
        (*stkA)->head->next->data.keep_in_stk = 1;
        swap(stkA, stkB, 'a', 'w');
    }
    else if ((*stkA)->head->data.keep_in_stk == 1 && (*stkA)->tail->data.keep_in_stk == 0 &&
        check_indexA((*stkA)->tail->data.index, (*stkA)->head->data.index, nk))
    {
        (*stkA)->tail->data.keep_in_stk = 1;
        rev_rotate(stkA, stkB, 'a', 'w');
        swap(stkA, stkB, 'a', 'w');
    }

}

void	action(t_List *stkA)
{
	t_List	*stkB;
	size_t	count_unsort_elem;

	stkB = created_list();
    print_List(stkA);
	while (1)
	{
        check_elem(&stkA, &stkB);
		if (stkA->head->data.keep_in_stk == 1)
		{
			count_unsort_elem = check_unsort_elm(stkA);
			if (count_unsort_elem != 0)
				rotate(&stkA, &stkB, 'a', 'w');
			else
				last_actions(stkA, stkB);
		}
		else
		{
			push(&stkA, &stkB, 'b', 'w');
		}
	}
}
