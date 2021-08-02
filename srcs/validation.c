#include "../push_swap.h"

void 	ft_check_chunk(char *s)
{
	int	i;
	
	i = 0;
	while (s[i])
	{
		if (i == 0 && (s[i] == '-' || s[i] == '+') && s[i + 1] && ft_isdigit(s[i + 1]))
			i += 2;
		else if (ft_isdigit(s[i]))
			i++;
		else
			ft_error("No valid arguments\n");
	}
}

t_data	init_data(char *str)
{
	t_data	data;
	
	data.value = ft_atoi(str);
	data.pos_in_stack = -1;
	data.index = -1;
	data.keep_in_stack = 0;
	return (data);
}

t_compare	sort_data_init(Node *current_i, size_t i)
{
	struct s_compare	sort;
	
	sort.pos_min = i;
	sort.min = current_i->data.value;
	sort.pos_max = i;
	sort.max = current_i->data.value;
	return (sort);
}

t_compare	comparison(DblLinkedList **stack, Node *current_i, size_t i)
{
	size_t		j;
	t_compare	sort;
	Node 		*current_j;
	
	sort = sort_data_init(current_i, i);
	j = i + 1;
	while (j < (*stack)->size)
	{
		current_j = getNthq(*stack, j);
		if (current_j->data.value < sort.min && (int)current_j->data.index == -1)
		{
			sort.min = current_j->data.value;
			sort.pos_min = j;
		}
		else if (current_j->data.value > sort.max && (int)current_j->data.index == -1)
		{
			sort.max = current_j->data.value;
			sort.pos_max = j;
		}
		else if (current_j->data.value == sort.min || current_j->data.value == sort.max)
			ft_error("Duplicate number\n");
		j++;
	}
	return (sort);
}

void	check_dup_and_index(DblLinkedList *stack)
{
	size_t		i;
	size_t		k;
	size_t 		index;
	size_t 		size;
	Node		*current_i;
	Node 		*current_j;
	t_compare	sort;
	
	i = 0;
	index = 0;
	size = stack->size;
	k = size - 1;
	while (i < size)
	{
		current_i = getNthq(stack, i);
		current_i->data.pos_in_stack = i;
		while ((int)current_i->data.index == -1)
		{
			sort = comparison(&stack, current_i, i);
			current_j = getNthq(stack, sort.pos_min);
			current_j->data.index = index++;
			current_j = getNthq(stack, sort.pos_max);
			current_j->data.index = k--;
		}
		i++;
	}
}

DblLinkedList	*ft_validate_data(char **argv)
{
	int				i;
	int 			j;
	char    		**chunk;
	DblLinkedList	*stack;
	t_data			data;
	
	stack = createDblLinkedList();
	i = 1;
	while (argv[i])
	{
		j = 0;
		chunk = ft_split(argv[i], ' ');
		while (chunk[j])
		{
			ft_check_chunk(chunk[j]);
			data = init_data(chunk[j]);
			pushBack(stack, data);
			free(chunk[j]);
			j++;
		}
		free(chunk);
		i++;
	}
	check_dup_and_index(stack);
	return (stack);
}

/******************************************/

Node	*current_next(Node *list, DblLinkedList *stack)
{
	Node	*current;
	
	if (list->next == NULL)
		current = stack->head;
	else
		current = list->next;
	return (current);
}

Node	*current_prev(Node *list, DblLinkedList *stack)
{
	Node	*current;
	
	if (list->prev == NULL)
		current = stack->tail;
	else
		current = list->prev;
	return (current);
}

size_t	GetCeilIndex(DblLinkedList *stack, t_best *best, size_t lenght, size_t key)
{
	int		left;
	int 	right;
	int		middle;
	Node 	*current;
	
	left = -1;
	right = (int)lenght - 1;
	while (right - left > 1)
	{
		middle = left + (right - left) / 2;
		current = getNthq(stack, best[middle].tailIndexes);
		if (current->data.index >= key)
			right = middle;
		else
			left = middle;
	}
	return (right);
}

size_t	LongestIncreasingSubsequence(DblLinkedList *stack, Node *tmp)
{
	size_t 	i;
	size_t	position;
	size_t	lenght;
	t_best	*best;
	Node	*current;
	
	best = malloc(sizeof(t_best) * (stack->size + 1));
	if (!best)
		ft_error("Malloc error\n");
	i = 0;
	while (i < stack->size + 1)
	{
		best[i].tailIndexes = 0;
		best[i].prevIndexes = -1;
		i++;
	}
	i = 1;
	lenght = 1;
	while (i < stack->size)
	{
		current = current_next(tmp, stack);
		Node *current_begin = getNthq(stack, best[0].tailIndexes);
		Node *current_back = getNthq(stack, best[lenght - 1].tailIndexes);
		if (current->data.index < current_begin->data.index)
			best[0].tailIndexes = i;
		else if (current->data.index > current_back->data.index)
		{
			best[i].prevIndexes = best[lenght - 1].tailIndexes;
			best[lenght].tailIndexes = i;
			lenght++;
		}
		else
		{
			position = GetCeilIndex(stack, best, lenght, current->data.index);
			best[i].prevIndexes = best[position - 1].tailIndexes;
			best[position].tailIndexes = i;
		}
		tmp = tmp->next;
		i++;
	}
	i = 0;
	while (i < stack->size + 1)
	{
		ft_printf("%d\t", best[i].prevIndexes);
		i++;
	}
	return (lenght);
}

//t_position	find_best_sort_stack(DblLinkedList *stack)
//{
//	Node 	*tmp;
//	size_t	lenght;
//
//	tmp = stack->head;
//	while (tmp)
//	{
//		lenght = LongestIncreasingSubsequence(stack, tmp);
//		tmp = tmp->next;
//	}
//}
//
//t_position markup_stack(DblLinkedList *stack)
//{
//
//	printDblLinkedList(stack);
//
//	return (best_stack);
//}
