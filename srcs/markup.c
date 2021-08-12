#include "../push_swap.h"

/********************* Subseq initialization *********************/

static void	init_subseq(t_List *stk, t_best **subseq)
{
	size_t	i;

	i = 0;
	while (i < stk->size + 1)
	{
		(*subseq)[i].tailInd = 0;
		(*subseq)[i].prevInd = -1;
		i++;
	}
	(*subseq)->lenght = 1;
	(*subseq)->stk = stk;
}

/************* Search for the longest increasing subsequence *************/

static void	LongestIncreasingSubseq(t_List *stk, t_best **subseq)
{
	size_t	i;
	t_Node	*cur;	

	i = 1;
	init_subseq(stk, subseq);
	cur = stk->head;
	while (i < stk->size)
	{
		cur = cur->next;
		incrSubseq(stk, subseq, cur, i);
		i++;
	}
}
/**************** Finding the maximum number of sorted items ****************/

static void	find_best_sort_stk(t_List *stk, t_best **best_stk)
{
	size_t	i;
	t_best	*subseq;
	t_List	*tmp;

	i = 0;
	tmp = stk;
	init_subseq(tmp, best_stk);
	subseq = *best_stk;
	while (i++ < stk->size)
	{
		LongestIncreasingSubseq(tmp, &subseq);
		if (subseq->lenght > (*best_stk)->lenght)
		{
			subseq->iteration = i;
			(*best_stk) = subseq;
		}
		rotate(&tmp, NULL, 'a', 'n');
	}
}

/*********************  Markup stack *********************/

void	markup_stack(t_List *stk)
{
	size_t	i;
	t_best	*best_stk;
	t_Node	*cur;

	best_stk = malloc(sizeof(t_best) * (stk->size + 1));
	if (!best_stk)
		ft_error("Malloc error\n");
	find_best_sort_stk(stk, &best_stk);
	i = 0;
	while (i++ < best_stk->iteration)
		rotate(&stk, NULL, 'a', 'n');
	i = best_stk[best_stk->lenght - 1].tailInd;
	while ((int)i >= 0)
	{
		cur = getNthq(best_stk->stk, i - 1);
		cur->data.keep_in_stk = 1;
		i = best_stk[i].prevInd;
	}
	i = 0;
	while (i++ < best_stk->iteration)
		rev_rotate(&stk, NULL, 'a', 'n');
	free(best_stk);
}
