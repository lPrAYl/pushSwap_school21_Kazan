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

t_position	best_stack_init()
{
	t_position	best_stack;
	
	best_stack.index_begin = 0;
	best_stack.step = 0;
	best_stack.count_elem = 0;
	return (best_stack);
}

t_position	fill_best_stack(size_t index_begin, size_t step, size_t count_elem)
{
	t_position	best_stack;
	
	best_stack.index_begin = index_begin;
	best_stack.step = step;
	best_stack.count_elem = count_elem;
	return (best_stack);
}

t_position	find_count_sort_numb(DblLinkedList *stack, Node *tmp, t_position best_stack, size_t step)
{
	size_t		index_begin;
	size_t		index_end;
	size_t		count_elem;
	size_t		j;
	Node		*current_forward;
	Node		*current_back;
	
	index_begin = tmp->data.index;
	index_end = index_begin;
	current_forward = current_next(tmp, stack);
	current_back = current_prev(tmp, stack);
	count_elem = 1;
	j = 0;
	size_t k = 0;
	while (current_forward->data.index != index_begin && current_back->data.index != index_end)
	{
		if (current_forward->data.index > index_begin + k * step && current_forward->data.index <= index_begin + (k + 1) * step)
		{
			if (current_forward->data.index == index_begin + (k + 1) * step)
			{
				index_end = current_forward->data.index;
				k++;
			}
			count_elem++;
		}
		if (current_back->data.index < index_end - k * step && current_forward->data.index >= index_end - (k + 1) * step)
		{
			if (current_back->data.index == index_end - (k + 1) * step)
			{
				index_begin = current_back->data.index;
				k++;
			}
			count_elem++;
		}
		current_forward = current_next(current_forward, stack);
		current_back = current_prev(current_back, stack);
	}
	if (count_elem > best_stack.count_elem)
		best_stack = fill_best_stack(index_begin, step, count_elem);
	return (best_stack);
}

t_position	find_best_sort_stack(DblLinkedList *stack)
{
	size_t		step;
	Node		*tmp;
	t_position	best_stack;
	
	tmp = stack->head;
	best_stack = best_stack_init();
	while (tmp)
	{
		step = 1;
		while (step * step < stack->size)
		{
			best_stack = find_count_sort_numb(stack, tmp, best_stack, step);
			step++;
		}
		tmp = tmp->next;
	}
	return (best_stack);
}

t_position markup_stack(DblLinkedList *stack)
{
	//size_t		pos;
	//size_t		index;
	//Node		*current;
	//Node		*tmp;
	t_position	best_stack;
	
	
	best_stack = find_best_sort_stack(stack);
	ft_printf("%d\n", best_stack.index_begin);
	ft_printf("%d\n", best_stack.step);
	ft_printf("%d\n", best_stack.count_elem);
	//if (best_stack.count_elem == stack->size)
	//{
	//	pos = best_stack.position_begin;
	//
	//	if (pos < stack->size / 2 && pos > 0)
	//		while (pos--)
	//			ra(&stack);
	//	else if (pos >= stack->size / 2)
	//		while (pos++ < stack->size)
	//			rra(&stack);
	//	ft_putstr_fd("List is sorted\n", 1);
	//	exit(EXIT_SUCCESS);
	//}
	//printDblLinkedList(stack);
	//
	//
	//tmp = getNthq(stack, best_stack.position_begin);
	//tmp->data.keep_in_stack = 1;
	//index = tmp->data.index;
	//current = current_next(tmp, stack);
	//while (current->data.index != tmp->data.index)
	//{
	//	if (current->data.index > index )
	//	{
	//		current->data.keep_in_stack = 1;
	//		index = current->data.index;
	//	}
	//	current = current_next(current, stack);
	//}
	printDblLinkedList(stack);
	//{
	//	i = 0;
	//	while (i < best_stack->count_elem)
	//	{
	//		if (tmp->data.index == best_stack->begin + i * best_stack->step)
	//		{
	//			tmp_pos = tmp;
	//			tmp->data.keep_in_stack = 1;
	//			index_begin = tmp->data.index;
	//			begin = index_begin;
	//			if (index_begin == best_stack->begin)
	//			{
	//				while (tmp_pos->prev && tmp_pos->prev->data.keep_in_stack == 0)
	//				{
	//					size_t j = 2;
	//					while (j <= best_stack->step)
	//					{
	//						if (tmp_pos->prev->data.index < begin  &&
	//								tmp_pos->prev->data.keep_in_stack == 0)
	//						{
	//							begin = tmp_pos->prev->data.index;
	//							tmp_pos->prev->data.keep_in_stack = 1;
	//						}
	//						j++;
	//					}
	//					tmp_pos = tmp_pos->prev;
	//				}
	//			}
	//			else if (index_begin == best_stack->begin + (best_stack->count_elem - 1) * best_stack->step)
	//			{
	//				while (tmp_pos->next && tmp_pos->next->data.keep_in_stack == 0)
	//				{
	//					size_t j = 2;
	//					while (j <= best_stack->step)
	//					{
	//						if (tmp_pos->next->data.index > begin &&
	//								tmp_pos->next->data.keep_in_stack == 0)
	//						{
	//							begin = tmp_pos->next->data.index;
	//							tmp_pos->next->data.keep_in_stack = 1;
	//						}
	//						j++;
	//					}
	//					tmp_pos = tmp_pos->next;
	//				}
	//			}
	//			else
	//			{
	//				while (tmp_pos->next && tmp_pos->next->data.keep_in_stack == 0 && tmp_pos->next->data.index != index_begin + best_stack->step)
	//				{
	//					size_t j = 2;
	//					while (j <= best_stack->step)
	//					{
	//						if (tmp_pos->next->data.index > begin && tmp_pos->next->data.index < index_begin + j &&
	//							tmp_pos->next->data.keep_in_stack == 0)
	//						{
	//							begin = tmp_pos->next->data.index;
	//							tmp_pos->next->data.keep_in_stack = 1;
	//						}
	//						j++;
	//					}
	//					tmp_pos = tmp_pos->next;
	//				}
	//			}
	//		}
	//		i++;
	//	}
	//	tmp = tmp->next;
	//}
	
	return (best_stack);
}
