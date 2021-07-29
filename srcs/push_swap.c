#include "../push_swap.h"

void	ft_error(char *s)
{
	ft_putstr_fd(s, 1);
	exit(EXIT_FAILURE);
}

int main(int argc, char **argv)
{
	DblLinkedList	*stackA;
	t_position		best_stack;

	if (argc > 1)
	{
		stackA = ft_validate_data(argv);
		best_stack = markup_stack(stackA);
		//printDblLinkedList(stackA);
		//operation(stackA, best_stack);
		//pb(&stackA, &stackB);
		//pa(&stackA, &stackB);
		//ra(&stackA);
		//rra(&stackA);
		//printDblLinkedList(stackA);
		//printDblLinkedList(stackB);
	}
	else
		ft_error("Not enough arguments\n");
	return (0);
}

