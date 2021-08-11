#include "../../push_swap.h"

static void	push_action(DblLinkedList **stack_from, DblLinkedList **stack_to)
{
    t_data	data;
    Node	*tmp_to;
    Node    *tmp_from;

    if (*stack_from == NULL)
        return ;
    data = popFront(*stack_from);
    data.pos_in_stack = 0;
    tmp_to = (*stack_to)->head;
    tmp_from = (*stack_from)->head;
    while (tmp_to)
    {
        tmp_to->data.pos_in_stack++;
        tmp_to = tmp_to->next;
    }
    while (tmp_from)
    {
        tmp_from->data.pos_in_stack--;
        tmp_from = tmp_from->next;
    }
    pushFront(*stack_to, data);
}

void	push(DblLinkedList **stackA, DblLinkedList **stackB, char stack, char write)
{
    if (stack == 'a')
    {
        push_action(stackB, stackA);
        if (write == 'w')
            ft_putstr_fd("pa\n", 1);
    }
    else if (stack == 'b')
    {
        push_action(stackA, stackB);
        if (write == 'w')
            ft_putstr_fd("pb\n", 1);
    }

}

