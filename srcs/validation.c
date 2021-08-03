#include "../push_swap.h"

void 	ft_check_chunk(char *str)
{
	int	i;
	
	i = 0;
	if ((ft_strncmp(str, "2147483647", 10) > 0 && ft_strlen(str) == 10) ||
			(ft_strncmp(str, "-2147483648", 11) > 0 && ft_strlen(str) == 11))
		ft_error("Overflow int\n");
	while (str[i])
	{
		if (i == 0 && (str[i] == '-' || str[i] == '+') && str[i + 1] && ft_isdigit(str[i + 1]))
			i += 2;
		else if (ft_isdigit(str[i]))
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

size_t	GetCeilIndex(DblLinkedList *tmp, t_best *best, size_t lenght, size_t key)
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
		current = getNthq(tmp, best[middle].tailIndexes);
		if (current->data.index >= key)
			right = middle;
		else
			left = middle;
	}
	return (right);
}

t_best 	*LongestIncreasingSubsequence(DblLinkedList *tmp)
{
	size_t 	i;
	size_t	position;
	t_best	*best;
	Node	*current;
	
	best = malloc(sizeof(t_best) * (tmp->size + 1));
	if (!best)
		ft_error("Malloc error\n");
	i = 0;
	while (i < tmp->size + 1)
	{
		best[i].tailIndexes = 0;
		best[i].prevIndexes = -1;
		i++;
	}
	best->lenght = 1;
	i = 1;
	current = tmp->head;
	while (i < tmp->size)
	{
		current = current->next;
		Node *current_begin = getNthq(tmp, best[0].tailIndexes);
		Node *current_back = getNthq(tmp, best[best->lenght - 1].tailIndexes);
		if (current->data.index < current_begin->data.index)
			best[0].tailIndexes = i;
		else if (current->data.index > current_back->data.index)
		{
			best[i].prevIndexes = best[best->lenght - 1].tailIndexes;
			best[best->lenght].tailIndexes = i;
			best->lenght++;
		}
		else
		{
			position = GetCeilIndex(tmp, best, best->lenght, current->data.index);
			best[i].prevIndexes = best[position - 1].tailIndexes;
			best[position].tailIndexes = i;
		}
		i++;
	}
	return (best);
}

t_best 	*find_best_sort_stack(DblLinkedList *stack)
{
	DblLinkedList	*tmp;
	size_t	i;
	size_t	lenght;
	t_best	*best;
	t_best	*best_tmp;

	tmp = stack;
	
	lenght = 1;
	i = 0;
	while (i < tmp->size)
	{
		best = LongestIncreasingSubsequence(tmp);
		if (best->lenght > lenght)
		{
			best->stack = tmp;
			lenght = best->lenght;
			best_tmp = best;
			
		}
		ra(&tmp);
		i++;
	}
	
	ft_printf("%d\n", best_tmp->lenght);
	size_t j = best_tmp[best->lenght - 1].tailIndexes;
	while ((int)j >= 0)
	{
		Node *current = getNthq(best_tmp->stack, j);
		ft_printf("%d\t", current->data.value);
		j = best_tmp[j].prevIndexes;
	}
	ft_printf("%d\n", best_tmp->lenght);
	ft_printf("\n");
	return (best_tmp);
}

void	markup_stack(DblLinkedList *stack)
{
	size_t	i;
	t_best	*best_stack;
	Node	*current;
	
	best_stack = find_best_sort_stack(stack);
	i = best_stack[best_stack->lenght - 1].tailIndexes;
	while ((int)i >= 0)
	{
		current = getNthq(best_stack->stack, i);
		current->data.keep_in_stack = 1;
		i = best_stack[i].prevIndexes;
	}
	printDblLinkedList(stack);
}
