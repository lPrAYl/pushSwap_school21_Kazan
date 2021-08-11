#include "../push_swap.h"

void	ft_error(char *s)
{
	ft_putstr_fd(s, 1);
	exit(EXIT_FAILURE);
}

int main(int argc, char **argv)
{
	DblLinkedList	*stackA;
	
	if (argc > 1)
	{
		stackA = ft_validate_data(argv);
		markup_stack(stackA);
		while (1);
		operation(stackA);
	}
	else
		ft_error("Not enough arguments\n");
	return (0);
}

