#include "../push_swap.h"

void ft(void)
{

}

//int	find_best_path(DblLinkedList *stackA)
//{
//	Node 	*tmp;
//	size_t	do_begin;
//	size_t	do_end;
//	int		direction;
//
//	do_begin = 1;
//	do_end = 1;        ;
//	tmp = stackA->head;
//	while (tmp->data.keep_in_stack == 1 && tmp->next != NULL)
//	{
//		do_begin++;
//		tmp = tmp->next;
//	}
//	tmp = stackA->tail;
//	while (tmp->data.keep_in_stack == 1 && tmp->prev != NULL)
//	{
//		do_end++;
//		tmp = tmp->prev;
//	}
//	if (do_begin < do_end)
//		direction = (int)do_begin;
//	else if (do_begin == stackA->size)
//		direction = 0;
//	else
//		direction = (-1) * ((int)do_end);
//	//ft_printf("%d\t%d\n", do_begin, direction);
//	return (direction);
//}
//
//void	operation(DblLinkedList *stackA, t_position *best_stack)
//{
//	DblLinkedList	*stackB;
//	Node			*tmp_head_A;
//	Node 			*tmp_tail_A;
//	Node			*tmp_head_B;
//	Node 			*tmp_tail_B;
//	Node			*tmp_next;
//	Node			*tmp_prev;
//	size_t			next_keep_in_stack;
//	size_t			prev_keep_in_stack;
//	int 			direction;
//
//
//	stackB = createDblLinkedList();
//
//	int	i = 0;
//	int test = 18;
//	while (i < test)
//	{
//		tmp_head_A = stackA->head;
//		tmp_tail_A = stackA->tail;
//		tmp_head_B = stackB->head;
//		tmp_tail_B = stackB->tail;
//
//		/********** find next/prev keep_in_stack element **********/
//
//		tmp_next = tmp_head_A->next;
//		while (tmp_next->data.keep_in_stack != 1) {
//			tmp_next = tmp_next->next;
//		}
//		next_keep_in_stack = tmp_next->data.index;
//
//		tmp_prev = tmp_tail_A;
//		while (tmp_prev->data.keep_in_stack != 1) {
//			tmp_prev = tmp_prev->prev;
//		}
//		prev_keep_in_stack = tmp_prev->data.index;
//
//
//		if (i == test - 1)
//		{
//			ft_printf("%d\t", next_keep_in_stack);
//			ft_printf("%d\t", prev_keep_in_stack);
//			if (stackB->size > 0)
//				ft_printf("%d\t", tmp_head_B->data.index);
//			ft_printf("%d\t", tmp_head_A->data.index);
//			ft_printf("%d\n", tmp_head_A->data.index - best_stack->step);
//			printDblLinkedList(stackA);
//			printDblLinkedList(stackB);
//		}
//
//
//		if (tmp_head_A->data.keep_in_stack == 1)
//		{
//			/********** check current, next and previous index in StackB **********/
//
//			if (stackB->size > 0 && tmp_head_B->data.index > tmp_head_A->data.index && tmp_head_B->data.index < tmp_head_A->data.index + best_stack->step
//				&& (tmp_head_B->data.index < next_keep_in_stack || (tmp_head_B->data.index > next_keep_in_stack && next_keep_in_stack <
//				tmp_head_A->data.index)))
//			{
//				tmp_head_B->data.keep_in_stack = 1;
//				ra(&stackA);
//				pa(&stackA, &stackB);
//			}
//			else if	(stackB->size > 0 && tmp_head_B->data.index < tmp_head_A->data.index && tmp_head_B->data.index > tmp_head_A->data.index - best_stack->step
//					&& (tmp_head_B->data.index > prev_keep_in_stack || (tmp_head_B->data.index < prev_keep_in_stack && prev_keep_in_stack >
//					tmp_head_A->data.index)))
//			{
//				tmp_head_B->data.keep_in_stack = 1;
//				pa(&stackA, &stackB);
//			}
//			else if (stackB->size > 1 && tmp_head_B->next->data.index > tmp_head_A->data.index && tmp_head_B->next->data.index < tmp_head_A->data.index + best_stack->step
//					&& (tmp_head_B->next->data.index < next_keep_in_stack || (tmp_head_B->next->data.index > next_keep_in_stack && next_keep_in_stack <
//					tmp_head_A->data.index)))
//			{
//				tmp_head_B->next->data.keep_in_stack = 1;
//				rr(&stackA, &stackB);
//				pa(&stackA, &stackB);
//			}
//			else if (stackB->size > 1 && tmp_head_B->next->data.index < tmp_head_A->data.index && tmp_head_B->next->data.index > tmp_head_A->data.index - best_stack->step
//					&& (tmp_head_B->next->data.index > prev_keep_in_stack || (tmp_head_B->next->data.index < prev_keep_in_stack && prev_keep_in_stack >
//					tmp_head_A->data.index)))
//			{
//				tmp_head_B->next->data.keep_in_stack = 1;
//				rb(&stackB);
//				pa(&stackA, &stackB);
//			}
//			else if (stackB->size > 0 && tmp_tail_B->data.index > tmp_head_A->data.index && tmp_tail_B->data.index < tmp_head_A->data.index + best_stack->step
//					&& (tmp_tail_B->data.index < next_keep_in_stack || (tmp_tail_B->data.index > next_keep_in_stack && next_keep_in_stack <
//					tmp_head_A->data.index)))
//			{
//				tmp_tail_B->data.keep_in_stack = 1;
//				ra(&stackA);
//				rrb(&stackB);
//				pa(&stackA, &stackB);
//			}
//			else if (stackB->size > 0 && tmp_tail_B->data.index < tmp_head_A->data.index && tmp_tail_B->data.index > tmp_head_A->data.index - best_stack->step
//					&& (tmp_tail_B->data.index > prev_keep_in_stack || (tmp_tail_B->data.index < prev_keep_in_stack && prev_keep_in_stack >
//					 tmp_head_A->data.index)))
//			{
//				tmp_tail_B->data.keep_in_stack = 1;
//				rrb(&stackB);
//				pa(&stackA, &stackB);
//			}
//			//printDblLinkedList(stackA);
//
//			/********** Check next index in StackA  **********/
//
//			if (tmp_head_A->next->data.keep_in_stack == 1)
//			{
//				direction = find_best_path(stackA);
//				//ft_printf("%d\n", direction);
//				if (direction > 0)
//				{
//					if (stackB->size > 1 && stackB->head->data.index < stackB->tail->data.index)
//						rr(&stackA, &stackB);
//					else
//						ra(&stackA);
//				}
//				else if (direction < 0 || stackA->tail->data.keep_in_stack == 0)
//				{
//					if (stackB->size > 1 && stackB->head->data.index < stackB->tail->data.index)
//						rrr(&stackA, &stackB);
//					else
//						rra(&stackA);
//				}
//				else
//				{
//					if (stackB->size == 0)
//					{
//						size_t pos = stackA->head->data.pos_in_stack;
//						if (pos < stackA->size / 2 && pos > 0)
//							while (pos--)
//								ra(&stackA);
//						else if (pos >= stackA->size / 2)
//							while (pos++ < stackA->size)
//								rra(&stackA);
//						ft_putstr_fd("List is sorted\n", 1);
//						exit(EXIT_SUCCESS);
//					}
//				}
//			}
//			else
//			{
//				//printDblLinkedList(stackA);
//				if (tmp_head_A->next->data.index < tmp_head_A->data.index && tmp_head_A->next->data.index > prev_keep_in_stack ||
//					(tmp_head_A->next->data.index > prev_keep_in_stack && prev_keep_in_stack < tmp_head_A->data.index))
//				{
//					tmp_head_A->next->data.keep_in_stack = 1;
//					if (tmp_head_B->data.index < tmp_head_B->next->data.index)
//						ss(&stackA, &stackB);
//					else
//						sa(&stackA);
//				}
//				else
//				{
//					if (stackB->size > 0 && tmp_head_B->data.index < tmp_head_B->next->data.index)
//						ss(&stackA, &stackB);
//					else
//						sa(&stackA);
//					pb(&stackA, &stackB);
//				}
//				//printDblLinkedList(stackA);
//			}
//		}
//		else	/********** Check index in StackA if keep_in_stack = 0 **********/
//		{
//			if (tmp_head_A->data.index > tmp_head_A->next->data.index)
//			{
//				if (tmp_head_A->next->data.keep_in_stack == 1 && tmp_head_A->data.index < tmp_head_A->next->data.index + best_stack->step
//					&& (tmp_head_A->data.index < next_keep_in_stack || (tmp_head_A->data.index > next_keep_in_stack && next_keep_in_stack < tmp_head_A->next->data.index)))
//				{
//					tmp_head_A->data.keep_in_stack = 1;
//					if (tmp_head_B->data.index < tmp_head_B->next->data.index)
//						ss(&stackA, &stackB);
//					else
//						sa(&stackA);
//				}
//				else if (tmp_head_A->next->data.keep_in_stack == 0)
//				{
//					if (tmp_head_B->data.index < tmp_head_B->next->data.index)
//						ss(&stackA, &stackB);
//					else
//						sa(&stackA);
//				}
//				else
//					pb(&stackA, &stackB);
//			}
//			else if (tmp_head_A->data.index < tmp_tail_A->data.index && tmp_tail_A->data.keep_in_stack == 1 && tmp_head_A->data.index > tmp_tail_A->data.index - best_stack->step)
//			{
//				tmp_head_A->data.keep_in_stack = 1;
//				rra(&stackA);
//				sa(&stackA);
//			}
//			else
//				pb(&stackA, &stackB);
//		}
//
//		//if (i == test - 1) {
//		//	printDblLinkedList(stackA);
//		//	printDblLinkedList(stackB);
//		//}
//		i++;
//	}
//
//}

