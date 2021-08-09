#include "../push_swap.h"

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
	t_optActions	operations;


	stackB = createDblLinkedList();

	int	i = 0;
	int test = 190;
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
				direction = find_direction_to_rotate(stackA);
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
						//printDblLinkedList(stackA);
						exit(EXIT_SUCCESS);
					}
					else
					{
						operations = find_min_actions(stackA, stackB);
                        while (operations.ra-- > 0)
                            ra(&stackA);
                        while (operations.rb-- > 0)
                            rb(&stackB);
                        while (operations.rra-- > 0)
                            rra(&stackA);
                        while (operations.rrb-- > 0)
                            rrb(&stackB);
                        while (operations.rr-- > 0)
                            rr(&stackA, &stackB);
                        while (operations.rrr-- > 0)
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
