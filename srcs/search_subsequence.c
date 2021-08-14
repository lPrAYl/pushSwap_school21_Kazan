#include "../push_swap.h"

/********************* Getting the ceiling index *********************/

static size_t	GetCeilIndex(t_List *tmp, t_best **subseq, size_t key)
{
	int		left;
	int		right;
	int		middle;
	t_Node	*cur;

	left = -1;
	right = (int)(*subseq)->lenght - 1;
	while (right - left > 1)
	{
		middle = left + (right - left) / 2;
		cur = getNthq(tmp, (*subseq)[middle].tailInd);
		if (cur->data.index >= key)
			right = middle;
		else
			left = middle;
	}
	return (right);
}

/***************** Search for the increasing subseq *****************/

void	incrSubseq(t_List *stk, t_best **subseq, t_Node *cur, size_t i)
{
	size_t	position;
	t_Node	*cur_begin;
	t_Node	*cur_back;

	cur_begin = getNthq(stk, (*subseq)[0].tailInd);
	cur_back = getNthq(stk, (*subseq)[(*subseq)->lenght - 1].tailInd);
	if (cur->data.index < cur_begin->data.index)
		(*subseq)[0].tailInd = i;
	else if (cur->data.index > cur_back->data.index)
	{
		(*subseq)[i].prevInd = (*subseq)[(*subseq)->lenght - 1].tailInd;
		(*subseq)[(*subseq)->lenght].tailInd = i;
		(*subseq)->lenght++;
	}
	else
	{
		position = GetCeilIndex(stk, subseq, cur->data.index);
		(*subseq)[i].prevInd = (*subseq)[position - 1].tailInd;
		(*subseq)[position].tailInd = i;
	}
}
