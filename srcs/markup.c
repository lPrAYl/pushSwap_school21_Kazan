#include "../push_swap.h"

/********************* Getting the ceiling index *********************/

static size_t	GetCeilIndex(DblLinkedList *tmp, t_best *subsequnce, size_t key)
{
	int		left;
	int 	right;
	int		middle;
	Node 	*current;
	
	left = -1;
	right = (int)subsequnce->lenght - 1;
	while (right - left > 1)
	{
		middle = left + (right - left) / 2;
		current = getNthq(tmp, subsequnce[middle].tailIndexes);
		if (current->data.index >= key)
			right = middle;
		else
			left = middle;
	}
	return (right);
}

/********************* Subsequence initialization *********************/

static t_best	*init_subsequence(DblLinkedList *stack)
{
	size_t	i;
	t_best	*subsequence;
	
	subsequence = malloc(sizeof(t_best) * (stack->size + 1));
	if (!subsequence)
		ft_error("Malloc error\n");
	i = 0;
	while (i < stack->size + 1)
	{
		subsequence[i].tailIndexes = 0;
		subsequence[i].prevIndexes = -1;
		i++;
	}
	subsequence->lenght = 1;
	subsequence->stack = stack;
	return (subsequence);
}

/********************* Search for the longest increasing subsequence *********************/

static t_best 	*LongestIncreasingSubsequence(DblLinkedList *stack)
{
	size_t 	i;
	size_t	position;
	t_best	*subsequence;
	Node	*current;
	
	i = 1;
	subsequence = init_subsequence(stack);
	current = stack->head;
	while (i < stack->size)
	{
		current = current->next;
		Node *current_begin = getNthq(stack, subsequence[0].tailIndexes);
		Node *current_back = getNthq(stack, subsequence[subsequence->lenght - 1].tailIndexes);
		if (current->data.index < current_begin->data.index)
			subsequence[0].tailIndexes = i;
		else if (current->data.index > current_back->data.index)
		{
			subsequence[i].prevIndexes = subsequence[subsequence->lenght - 1].tailIndexes;
			subsequence[subsequence->lenght].tailIndexes = i;
			subsequence->lenght++;
		}
		else
		{
			position = GetCeilIndex(stack, subsequence, current->data.index);
			subsequence[i].prevIndexes = subsequence[position - 1].tailIndexes;
			subsequence[position].tailIndexes = i;
		}
		i++;
	}
	return (subsequence);
}

/********************* Finding the maximum number of sorted items *********************/

static t_best 	*find_best_sort_stack(DblLinkedList *stack)
{
	size_t	i;
	size_t	lenght;
	t_best	*subsequence;
	t_best	*best_subsequence;
	DblLinkedList	*tmp;
	
	i = 0;
	lenght = 0;
	tmp = stack;
	int flag = 0;
    while (i < stack->size)
	{

        subsequence = NULL;
        subsequence = LongestIncreasingSubsequence(tmp);
        if (subsequence->lenght > lenght)
		{
            lenght = subsequence->lenght;
            subsequence->iteration = i;
            if (flag == 1) {
                free(best_subsequence);
            }
            best_subsequence = subsequence;
            flag = 1;
        }
        rotate(&tmp, NULL, 'a', 'n');
        i++;
    }
    free(subsequence);
    return (best_subsequence);
}

/*********************  Markup stack *********************/

void	markup_stack(DblLinkedList *stack)
{
	size_t	i;
	t_best	*best_stack;
	Node	*current;
	
	best_stack = find_best_sort_stack(stack);
	i = 0;
	while (i < best_stack->iteration)
	{
		rotate(&stack, NULL, 'a', 'n');
		i++;
	}
	i = best_stack[best_stack->lenght - 1].tailIndexes;
	while ((int)i >= 0)
	{
		current = getNthq(best_stack->stack, i);
		current->data.keep_in_stack = 1;
		i = best_stack[i].prevIndexes;
	}
	i = 0;
	while (i < best_stack->iteration)
	{
		reverse_rotate(&stack, NULL, 'a', 'n');
		i++;
	}
	free(best_stack);
}