#include "../push_swap.h"

int ft_abs(int numb)
{
    if (numb < 0)
        numb = -numb;
    return (numb);
}

int check_indexA(size_t index, size_t prev, size_t next)
{
    if (index > prev && index < next)
        return (1);
    else if (index < next && index < prev && prev > next)
        return (1);
    else if (index > next && index > prev && prev > next)
        return (1);
    return (0);
}

int check_indexB(size_t target, size_t index_one, size_t index_two)
{
    int step_to_index_one;
    int step_to_index_two;

    step_to_index_one = ft_abs((int)(index_one - target));
    step_to_index_two = ft_abs((int)(index_two - target));
    return (step_to_index_one - step_to_index_two);
}

static int	find_direction_to_rotate(DblLinkedList *stack)
{
	Node 	*tmp;
	size_t	do_ra;
	size_t	do_rra;
	int		direction;

	do_ra = 1;
	do_rra = 1;
	tmp = stack->head;
	while (tmp->data.keep_in_stack == 1 && tmp->next != NULL)
	{
		do_ra++;
		tmp = tmp->next;
	}
	tmp = stack->tail;
	while (tmp->data.keep_in_stack == 1 && tmp->prev != NULL)
	{
		do_rra++;
		tmp = tmp->prev;
	}
	if (do_ra < do_rra)
		direction = (int)do_ra;
	else if (do_ra == stack->size)
		direction = 0;
	else
		direction = (-1) * ((int)do_rra);
	return (direction);
}

static void do_actions(DblLinkedList **stackA, DblLinkedList **stackB, t_optActions actions)
{
    while (actions.ra-- > 0)
        rotate(stackA, stackB, 'a', 'w');
    while (actions.rb-- > 0)
        rotate(stackA, stackB, 'b', 'w');
    while (actions.rra-- > 0)
        reverse_rotate(stackA, stackB, 'a', 'w');
    while (actions.rrb-- > 0)
        reverse_rotate(stackA, stackB, 'b', 'w');
    while (actions.rr-- > 0)
        rotate(stackA, stackB, 's', 'w');
    while (actions.rrr-- > 0)
        reverse_rotate(stackA, stackB, 's', 'w');
    if ((*stackB)->size > 0)
    {
        (*stackB)->head->data.keep_in_stack = 1;
        push(stackA, stackB, 'a','w');
    }
}

void	operation(DblLinkedList *stackA)
{
	DblLinkedList	*stackB;
	Node            *tmp_next;
	Node			*tmp_prev;
	size_t			next_keep_in_stack;
	size_t			prev_keep_in_stack;
	int 			direction;
	t_optActions	actions;


	stackB = createDblLinkedList();

	int	i = 0;
	int test = 229;
	while (i < test)
	{
		/********** find next/prev keep_in_stack element **********/

		find_markup_elem(stackA, stackA->head, &next_keep_in_stack, &prev_keep_in_stack);

		if (i == test - 1)
		{
		    ft_printf("%d\t", next_keep_in_stack);
		    ft_printf("%d\t", prev_keep_in_stack);
		    if (stackB->size > 0)
		        ft_printf("%d\t", stackB->head->data.index);
		    ft_printf("%d\t", stackA->head->data.index);
		    ft_printf("\n");
		    printDblLinkedList(stackA);
		    printDblLinkedList(stackB);
		}
		if (stackA->head->data.keep_in_stack == 1)
		{
		    if (stackB->size > 0)
		    {
		        actions = find_min_count_actions(stackA, stackB);
		        if (actions.total < 3)
		            do_actions(&stackA, &stackB, actions);
		        else if (actions.total < (int)stackB->size / 2 && actions.rrr + actions.ra + actions.rra < 5)
		            do_actions(&stackA, &stackB, actions);
		    }
		/********** Check next index in StackA  **********/

			if (stackA->head->next->data.keep_in_stack == 1 && stackA->tail->data.keep_in_stack == 1)
			{
				direction = find_direction_to_rotate(stackA);
				if (direction > 0)
				{
				    if (stackB->size > 1 && check_indexB(stackA->head->data.index, stackB->head->data.index, stackB->head->next->data.index) > 0)
						rotate(&stackA, &stackB, 's', 'w');
				    else
					    rotate(&stackA, &stackB, 'a', 'w');
				}
				else if (direction < 0)
				{
				    if (stackB->size > 1 && check_indexB(stackA->head->data.index, stackB->tail->data.index, stackB->head->data.index) < 0)
                        reverse_rotate(&stackA, &stackB, 's', 'w');
				    else
					    reverse_rotate(&stackA, &stackB, 'a', 'w');
				}
				else
				{
					if (stackB->size == 0)
					{
						size_t pos = stackA->head->data.index;
						if (pos < stackA->size / 2 + 1)
							while (pos--)
							    reverse_rotate(&stackA, &stackB, 'a', 'w');
						else
							while (pos++ < stackA->size)
							    rotate(&stackA, &stackB, 'a', 'w');
						ft_putstr_fd("List is sorted\n", 1);
						printDblLinkedList(stackA);
						printDblLinkedList(stackB);
						exit(EXIT_SUCCESS);
					}
					else
					{
						actions = find_min_count_actions(stackA, stackB);
						do_actions(&stackA, &stackB, actions);
					}
				}
			}
			else if (stackA->head->next->data.keep_in_stack == 0 || stackA->tail->data.keep_in_stack == 0)
			{
				if (stackA->head->next->data.keep_in_stack == 0 &&
				            check_indexA(stackA->head->next->data.index, prev_keep_in_stack, stackA->head->data.index))
				{
					stackA->head->next->data.keep_in_stack = 1;
					if (stackB->size > 1 && check_indexB(stackA->head->data.index, stackB->head->data.index, stackB->head->next->data.index) > 0)
						swap(&stackA, &stackB, 's', 'w');
					else
					    swap(&stackA, &stackB, 'a', 'w');
				}
				else if (stackA->tail->data.keep_in_stack == 0 &&
				                check_indexA(stackA->tail->data.index, stackA->head->data.index, next_keep_in_stack))
				{
				    stackA->tail->data.keep_in_stack = 1;
				    if (stackB->size > 1 && check_indexB(stackA->head->data.index, stackB->tail->data.index, stackB->head->data.index) > 0 &&
				            check_indexB(stackA->head->data.index, stackB->tail->data.index, stackB->head->next->data.index) < 0)
				    {
				        reverse_rotate(&stackA, &stackB, 's', 'w');
				        swap(&stackA, &stackB, 's', 'w');
				    }
				    else if (stackB->size > 1 && check_indexB(stackA->head->data.index, stackB->tail->data.index, stackB->head->data.index) < 0)
				    {
				        reverse_rotate(&stackA, &stackB, 's', 'w');
				        swap(&stackA, &stackB, 'a', 'w');
				    }
				    else if (stackB->size > 1 && check_indexB(stackA->head->data.index, stackB->head->data.index, stackB->head->next->data.index) < 0)
				    {
				        reverse_rotate(&stackA, &stackB, 'a', 'w');
				        swap(&stackA, &stackB, 's', 'w');
				    }
				    else
				    {
				        reverse_rotate(&stackA, &stackB, 'a', 'w');
				        swap(&stackA, &stackB, 'a', 'w');
				    }
				}
				else
				    if (stackA->head->next->data.keep_in_stack == 0)
				    {
				        if (stackB->size > 1 && check_indexB(stackA->head->data.index, stackB->head->data.index, stackB->head->next->data.index) > 0)
				            rotate(&stackA, &stackB, 's', 'w');
				        else
				            rotate(&stackA, &stackB, 'a', 'w');
				    }
				    else
				    {
				        if (stackB->size > 1 && check_indexB(stackA->head->data.index, stackB->tail->data.index, stackB->head->data.index) < 0)
				            reverse_rotate(&stackA, &stackB, 's', 'w');
				        else
                            reverse_rotate(&stackA, &stackB, 'a', 'w');
				    }

			}
		}
		else	/********** Check index in StackA if keep_in_stack = 0 **********/
		{
		    if (stackA->head->next->data.keep_in_stack == 1)
		    {
		        tmp_next = stackA->head->next->next;
		        while (tmp_next->data.keep_in_stack != 1)
		            tmp_next = tmp_next->next;
		        next_keep_in_stack = tmp_next->data.index;
		        if (check_indexA(stackA->head->data.index, stackA->head->next->data.index, next_keep_in_stack))
		        {
		            stackA->head->data.keep_in_stack = 1;
		            if (stackB->size > 1 && check_indexB(stackA->head->next->data.index, stackB->head->data.index, stackB->head->next->data.index) < 0)
		                swap(&stackA, &stackB, 's', 'w');
		            else
		                swap(&stackA, &stackB, 'a', 'w');
		        }
		        else
		            push(&stackA, &stackB, 'b', 'w');
		    }
		    else if (stackA->tail->data.keep_in_stack == 1)
		    {
		        tmp_prev = stackA->tail->prev;
		        while (tmp_prev->data.keep_in_stack != 1)
		            tmp_prev = tmp_prev->prev;
		        prev_keep_in_stack = tmp_prev->data.index;
		        if (check_indexA(stackA->head->data.index, prev_keep_in_stack, stackA->tail->data.index))
		        {
		            if (stackB->size > 1 && check_indexB(stackA->head->data.index, stackB->tail->data.index, stackB->head->data.index) > 0 &&
		            check_indexB(stackA->head->data.index, stackB->tail->data.index, stackB->head->next->data.index) < 0)
		            {
		                reverse_rotate(&stackA, &stackB, 's', 'w');
		                swap(&stackA, &stackB, 's', 'w');
		            }
		            else if (stackB->size > 1 && check_indexB(stackA->head->data.index, stackB->tail->data.index, stackB->head->data.index) < 0)
		            {
		                reverse_rotate(&stackA, &stackB, 's', 'w');
		                swap(&stackA, &stackB, 'a', 'w');
		            }
		            else if (stackB->size > 1 && check_indexB(stackA->head->data.index, stackB->head->data.index, stackB->head->next->data.index) < 0)
		            {
		                reverse_rotate(&stackA, &stackB, 'a', 'w');
		                swap(&stackA, &stackB, 's', 'w');
		            }
		            else
		            {
		                reverse_rotate(&stackA, &stackB, 'a', 'w');
		                swap(&stackA, &stackB, 'a', 'w');
		            }
		        }
		        else
		            push(&stackA, &stackB, 'b', 'w');
		    }
		    else
		        push(&stackA, &stackB, 'b', 'w');
		}
		i++;
	}
}

