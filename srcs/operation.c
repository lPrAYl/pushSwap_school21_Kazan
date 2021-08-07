#include "../push_swap.h"

int	ft_abs(int a, int b)
{
	int sign;
	
	sign = 1;
	if (a - b < 0)
		sign = -1;
	return (sign * (a - b));
}


int	find_best_path(DblLinkedList *stack)
{
	Node 	*tmp;
	size_t	do_begin;
	size_t	do_end;
	int		direction;

	do_begin = 1;
	do_end = 1;
	tmp = stack->head;
	while (tmp->data.keep_in_stack == 1 && tmp->next != NULL)
	{
		do_begin++;
		tmp = tmp->next;
	}
	tmp = stack->tail;
	while (tmp->data.keep_in_stack == 1 && tmp->prev != NULL)
	{
		do_end++;
		tmp = tmp->prev;
	}
	if (do_begin < do_end)
		direction = (int)do_begin;
	else if (do_begin == stack->size)
		direction = 0;
	else
		direction = (-1) * ((int)do_end);
	//ft_printf("%d\t%d\n", do_begin, direction);
	return (direction);
}

t_optOperations operation_init()
{
    t_optOperations count;

    count.ra = 0;
    count.rb = 0;
    count.rra = 0;
    count.rrb = 0;
    count.rr = 0;
    count.rrr = 0;
    return (count);
}

void	operation(DblLinkedList *stackA)
{
	DblLinkedList	*stackB;
	Node			*tmp_head_A;
	Node 			*tmp_tail_A;
	Node			*tmp_head_B;
	Node 			*tmp_tail_B;
	Node			*tmp_next;
	Node			*tmp_prev;
	size_t			next_keep_in_stack;
	size_t			prev_keep_in_stack;
	int 			direction;


	stackB = createDblLinkedList();

	int	i = 0;
	int test = 45;
	while (i < test)
	{
		tmp_head_A = stackA->head;
		tmp_tail_A = stackA->tail;
		tmp_head_B = stackB->head;
		tmp_tail_B = stackB->tail;

		/********** find next/prev keep_in_stack element **********/

		tmp_next = tmp_head_A->next;
		while (tmp_next->data.keep_in_stack != 1) {
			tmp_next = tmp_next->next;
		}
		next_keep_in_stack = tmp_next->data.index;

		tmp_prev = tmp_tail_A;
		while (tmp_prev->data.keep_in_stack != 1) {
			tmp_prev = tmp_prev->prev;
		}
		prev_keep_in_stack = tmp_prev->data.index;


		if (i == test - 1)
		{
			ft_printf("%d\t", next_keep_in_stack);
			ft_printf("%d\t", prev_keep_in_stack);
			if (stackB->size > 0)
				ft_printf("%d\t", tmp_head_B->data.index);
			ft_printf("%d\t", tmp_head_A->data.index);
			ft_printf("\n");
			printDblLinkedList(stackA);
			printDblLinkedList(stackB);
		}

		if (tmp_head_A->data.keep_in_stack == 1)
		{
			/********** check current, next and previous index in StackB **********/

			if (stackB->size > 0 && tmp_head_B->data.index > tmp_head_A->data.index &&
				(tmp_head_B->data.index < next_keep_in_stack || next_keep_in_stack < tmp_head_A->data.index))
			{
				tmp_head_B->data.keep_in_stack = 1;
				ra(&stackA);
				pa(&stackA, &stackB);
			}
			else if	(stackB->size > 0 && tmp_head_B->data.index < tmp_head_A->data.index &&
					(tmp_head_B->data.index > prev_keep_in_stack || prev_keep_in_stack > tmp_head_A->data.index))
			{
				tmp_head_B->data.keep_in_stack = 1;
				pa(&stackA, &stackB);
			}
			else if (stackB->size > 1 && tmp_head_B->next->data.index > tmp_head_A->data.index &&
					(tmp_head_B->next->data.index < next_keep_in_stack || next_keep_in_stack < tmp_head_A->data.index))
			{
				tmp_head_B->next->data.keep_in_stack = 1;
				rr(&stackA, &stackB);
				pa(&stackA, &stackB);
			}
			else if (stackB->size > 1 && tmp_head_B->next->data.index < tmp_head_A->data.index &&
					(tmp_head_B->next->data.index > prev_keep_in_stack || prev_keep_in_stack > tmp_head_A->data.index))
			{
				tmp_head_B->next->data.keep_in_stack = 1;
				rb(&stackB);
				pa(&stackA, &stackB);
			}
			else if (stackB->size > 2 && tmp_tail_B->data.index > tmp_head_A->data.index &&
					(tmp_tail_B->data.index < next_keep_in_stack || next_keep_in_stack < tmp_head_A->data.index))
			{
				tmp_tail_B->data.keep_in_stack = 1;
				ra(&stackA);
				rrb(&stackB);
				pa(&stackA, &stackB);
			}
			else if (stackB->size > 2 && tmp_tail_B->data.index < tmp_head_A->data.index &&
					(tmp_tail_B->data.index > prev_keep_in_stack || prev_keep_in_stack > tmp_head_A->data.index))
			{
				tmp_tail_B->data.keep_in_stack = 1;
				rrb(&stackB);
				pa(&stackA, &stackB);
			}
			//printDblLinkedList(stackA);

			/********** Check next index in StackA  **********/

			else if (tmp_head_A->next->data.keep_in_stack == 1 && tmp_tail_A->data.keep_in_stack == 1)
			{
				direction = find_best_path(stackA);
				//ft_printf("%d\n", direction);
				if (direction > 0)
				{
					if (stackB->size > 1 && stackB->head->data.index < stackB->tail->data.index)
						rr(&stackA, &stackB);
					else
						ra(&stackA);
				}
				else if (direction < 0 || stackA->tail->data.keep_in_stack == 0)
				{
					if (stackB->size > 1 && stackB->head->data.index < stackB->tail->data.index)
						rrr(&stackA, &stackB);
					else
						rra(&stackA);
				}
				else
				{
					if (stackB->size == 0)
					{
						size_t pos = stackA->head->data.index;
						if (pos < stackA->size / 2)
							while (pos--)
								rra(&stackA);
						else if (pos >= stackA->size / 2)
							while (pos++ < stackA->size)
								ra(&stackA);
						ft_putstr_fd("List is sorted\n", 1);
						printDblLinkedList(stackA);
						exit(EXIT_SUCCESS);
					}
					else
					{
					    t_optOperations  count;
					    size_t j = 0;
					    Node *current;
					    int RA;
					    int RB;
					    int RRA;
					    int RRB;

					    tmp_head_A = stackA->head;
					    tmp_tail_A = stackA->tail;
					    tmp_head_B = stackB->head;
					    tmp_tail_B = stackB->tail;
					    
					    count = operation_init();
						count.count = 2147483647;
					    while ((int)j < (int)(stackB->size / 2))
					    {
					        if (count.count < (int)j + 3)
					            break;

					        tmp_head_A = stackA->head;
					        tmp_tail_A = stackA->tail;

					        current = tmp_head_B;
					        while (!(((current->data.index > tmp_head_A->data.index && current->data.index < tmp_head_A->next->data.index)
					        		|| (current->data.index < tmp_head_A->next->data.index && tmp_head_A->next->data.index < tmp_head_A->data.index))
					                || ((current->data.index < tmp_tail_A->data.index && current->data.index > tmp_tail_A->prev->data.index)
					                || (current->data.index > tmp_tail_A->data.index && tmp_head_A->data.index < tmp_tail_A->data.index))))
					        {
					            tmp_head_A = tmp_head_A->next;
					            tmp_tail_A = tmp_tail_A->prev;
                            }
					        if (tmp_head_A->data.pos_in_stack < stackA->size / 2 && ((current->data.index > tmp_head_A->data.index && current->data.index < tmp_head_A->next->data.index)
					            || (current->data.index < tmp_head_A->next->data.index && tmp_head_A->next->data.index < tmp_head_A->data.index)))
                            {
                                RA = (int)tmp_head_A->data.pos_in_stack + 1;
                                RRA = (int)(tmp_head_A->data.pos_in_stack - stackA->size + 1);
                            }
                            else
                            {
                                RA = (int)tmp_tail_A->data.pos_in_stack;
                                RRA = (int)(tmp_tail_A->data.pos_in_stack - stackA->size);
                            }
					        RB = (int)j;
					        RRB = (int)(j - stackB->size);

					        int one = ft_max(RA, RB);
					        int two = ft_max(-RRA, -RRB);
					        int three = RA - RRB;
					        int four = RB - RRA;

					        if (one < count.count && one <= two && one <= three && one <= four)
					        {
					            count = operation_init();
					            count.count = one;
					            if (one == RA)
					            {
					                count.rr = RB;
					                count.ra = RA - RB;
					            }
					            else
					            {
					                count.rr = RA;
					                count.rb = RB - RA;
					            }
					        }
					        else if (two < count.count && two < one && two <= three && two <= four)
					        {
					            count = operation_init();
					            count.count = two;
					            if (two == -RRA)
					            {
					                count.rrr = -RRB;
					                count.rra = -(RRA - RRB);
					            }
					            else
					            {
					                count.rrr = -RRA;
					                count.rrb = -(RRB - RRA);
					            }
					        }
					        else if (three < count.count && three < one && three < two && three <= four)
					        {
					            count = operation_init();
					            count.count = three;
					            count.ra = RA;
					            count.rrb = -RRB;

					        }
					        else if (four < count.count && four < one && four < two && four < three)
					        {
					            count = operation_init();
					            count.count = four;
					            count.rb = RB;
					            count.rra = -RRA;
					        }

					        tmp_head_A = stackA->head;
					        tmp_tail_A = stackA->tail;

					        current = tmp_tail_B;
							while (!(((current->data.index > tmp_head_A->data.index && current->data.index < tmp_head_A->next->data.index)
									 || (current->data.index < tmp_head_A->next->data.index && tmp_head_A->next->data.index < tmp_head_A->data.index))
									 || ((current->data.index < tmp_tail_A->data.index && current->data.index > tmp_tail_A->prev->data.index)
									 || (current->data.index > tmp_tail_A->data.index && tmp_head_A->data.index < tmp_tail_A->data.index))))
					        {
					            tmp_head_A = tmp_head_A->next;
					            tmp_tail_A = tmp_tail_A->prev;
					        }
					        if (tmp_head_A->data.pos_in_stack < stackA->size / 2)
					        {
					            RA = (int)tmp_head_A->data.pos_in_stack + 1;
					            RRA = (int)(tmp_head_A->data.pos_in_stack - stackA->size + 1);
					        }
					        else
					        {
					            RA = (int)tmp_head_A->data.pos_in_stack;
					            RRA = (int)(tmp_tail_A->data.pos_in_stack - stackA->size);
					        }
					        RB = (int)(stackB->size - j - 1);
					        RRB = -((int)j + 1);

					        one = ft_max(RA, RB);
					        two = ft_max(-RRA, -RRB);
					        three = RA - RRB;
					        four = RB - RRA;

					        if (one < count.count && one <= two && one <= three && one <= four)
					        {
					            count = operation_init();
					            count.count = one;
					            if (one == RA)
					            {
					                count.rr = RB;
					                count.ra = RA - RB;
					            }
					            else
					            {
					                count.rr = RA;
					                count.rb = RB - RA;
					            }
					        }
					        else if (two < count.count && two < one && two <= three && two <= four)
					        {
					            count = operation_init();
					            count.count = two;
					            if (two == -RRA)
					            {
					                count.rrr = -RRB;
					                count.rra = -(RRA - RRB);
					            }
					            else
					            {
					                count.rrr = -RRA;
					                count.rrb = -(RRB - RRA);
					            }
					        }
					        else if (three < count.count && three < one && three < two && three <= four)
					        {
					            count = operation_init();
					            count.count = three;
					            count.ra = RA;
					            count.rrb = -RRB;

					        }
					        else if (four < count.count && four < one && four < two && four <= three)
					        {
					            count = operation_init();
					            count.count = four;
					            count.rb = RB;
					            count.rra = -RRA;
					        }

					        tmp_head_B = tmp_head_B->next;
					        tmp_tail_B = tmp_tail_B->prev;
					        j++;
					    }
                        while (count.ra-- > 0)
                            ra(&stackA);
                        while (count.rb-- > 0)
                            rb(&stackB);
                        while (count.rra-- > 0)
                            rra(&stackA);
                        while (count.rrb-- > 0)
                            rrb(&stackB);
                        while (count.rr-- > 0)
                            rr(&stackA, &stackB);
                        while (count.rrr-- > 0)
                            rrr(&stackA, &stackB);
                        stackB->head->data.keep_in_stack = 1;
                        pa(&stackA, &stackB);
					}
				}
			}
			else if (tmp_head_A->next->data.keep_in_stack == 0 || tmp_tail_A->data.keep_in_stack == 0)
			{
				//printDblLinkedList(stackA);
				if (tmp_head_A->next->data.keep_in_stack == 0 && tmp_head_A->next->data.index < tmp_head_A->data.index && tmp_head_A->next->data.index > prev_keep_in_stack)
				{
					tmp_head_A->next->data.keep_in_stack = 1;
					if (stackB->size > 1 && tmp_head_B->data.index < tmp_head_B->next->data.index)
						ss(&stackA, &stackB);
					else
						sa(&stackA);
				}
				else if (tmp_tail_A->data.keep_in_stack == 0 && tmp_tail_A->data.index > tmp_head_A->data.index && tmp_tail_A->data.index < next_keep_in_stack)
				{
				    tmp_tail_A->data.keep_in_stack = 1;
				    if (stackB->size > 2 && tmp_tail_B->data.index < tmp_head_B->data.index && tmp_tail_B->data.index > tmp_head_B->next->data.index)
				    {
				        rrr(&stackA, &stackB);
				        ss(&stackA, &stackB);
				    }
				    else if (stackB->size > 1 && tmp_tail_B->data.index > tmp_head_B->data.index)
				    {
				        rrr(&stackA, &stackB);
				        sa(&stackA);
				    }

				    else if (stackB->size > 2 && tmp_head_B->data.index < tmp_head_B->next->data.index)
				    {
				        rra(&stackA);
				        ss(&stackA, &stackB);
				    }
				    else
				    {
				        rra(&stackA);
				        sa(&stackA);
				    }
				}
				else
				{
					if (stackB->size > 1 && tmp_head_B->data.index < tmp_head_B->next->data.index && tmp_head_A->next->data.index < tmp_head_A->data.index)
						ss(&stackA, &stackB);
					else if (tmp_head_A->next->data.keep_in_stack == 0)
						ra(&stackA);
					else
					    rra(&stackA);
					pb(&stackA, &stackB);
				}
				//printDblLinkedList(stackA);
			}
		}
		else	/********** Check index in StackA if keep_in_stack = 0 **********/
		{
		    if (tmp_tail_A->data.keep_in_stack == 1)
		    {
		        tmp_prev = tmp_tail_A->prev;
		        while (tmp_prev->data.keep_in_stack != 1) {
		            tmp_prev = tmp_prev->prev;
		        }
		        prev_keep_in_stack = tmp_prev->data.index;
		    }
		    if (tmp_head_A->data.index < tmp_tail_A->data.index && tmp_tail_A->data.keep_in_stack == 1 && tmp_head_A->data.index > prev_keep_in_stack)
		    {
                tmp_head_A->data.keep_in_stack = 1;
                rra(&stackA);
                sa(&stackA);
		    }
			else if (tmp_head_A->data.index > tmp_head_A->next->data.index)
			{
				if (tmp_head_A->next->data.keep_in_stack == 1 && (tmp_head_A->data.index < next_keep_in_stack
					|| next_keep_in_stack < tmp_head_A->next->data.index))
				{
					tmp_head_A->data.keep_in_stack = 1;
					if (stackB->size > 1 && tmp_head_B->data.index < tmp_head_B->next->data.index)
						ss(&stackA, &stackB);
					else
						sa(&stackA);
				}
				else if (tmp_head_A->next->data.keep_in_stack == 0)
				{
					if (stackB->size > 1 && tmp_head_B->data.index < tmp_head_B->next->data.index)
						ss(&stackA, &stackB);
					else
						//sa(&stackA);
						pb(&stackA, &stackB);
				}
				else
					pb(&stackA, &stackB);
			}
			else
				pb(&stackA, &stackB);
		}
		i++;
	}
}

