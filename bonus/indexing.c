#include "../push_swap.h"

/**************** Initializing elements for comparison ****************/

static t_compare	init_sort_data(t_Node *cur_i, size_t i)
{
	struct s_compare	sort;

	sort.pos_min = i;
	sort.min = cur_i->data.value;
	sort.pos_max = i;
	sort.max = cur_i->data.value;
	return (sort);
}

/**************** Sorting and checking for duplicates ****************/

static t_compare	comparison(t_List **stk, t_Node *cur_i, size_t i)
{
	size_t		j;
	t_compare	sort;
	t_Node		*cur_j;

	sort = init_sort_data(cur_i, i);
	j = i + 1;
	while (j < (*stk)->size)
	{
		cur_j = getNthq(*stk, j);
		if (cur_j->data.value < sort.min && (int)cur_j->data.index == -1)
		{
			sort.min = cur_j->data.value;
			sort.pos_min = j;
		}
		else if (cur_j->data.value > sort.max && (int)cur_j->data.index == -1)
		{
			sort.max = cur_j->data.value;
			sort.pos_max = j;
		}
		else if (cur_j->data.value == sort.min || cur_j->data.value == sort.max)
			ft_error("Error\n");
		j++;
	}
	return (sort);
}

int	check_sorting(t_List *stk)
{
	t_Node	*tmp;

	tmp = stk->head;
	while (tmp->next && tmp->next->data.index > tmp->data.index)
		tmp = tmp->next;
	if (tmp->data.index == stk->tail->data.index)
		return (1);
	return (0);
}

/********************* Arrangement of indices *********************/

void	check_dup_and_index(t_List *stk, size_t index)
{
	size_t		i;
	size_t		j;
	t_Node		*cur_i;
	t_Node		*cur_j;
	t_compare	sort;

	i = 0;
	j = stk->size - 1;
	while (i < stk->size)
	{
		cur_i = getNthq(stk, i);
		cur_i->data.pos_in_stk = i;
		while ((int)cur_i->data.index == -1)
		{
			sort = comparison(&stk, cur_i, i);
			cur_j = getNthq(stk, sort.pos_min);
			cur_j->data.index = index++;
			cur_j = getNthq(stk, sort.pos_max);
			cur_j->data.index = j--;
		}
		i++;
	}
}
