#include "../push_swap.h"

int	main(int argc, char **argv)
{
	t_List	*stkA;

	if (argc > 1)
	{
		stkA = validate_data(argv);
		markup_stack(stkA);
		action(stkA);
	}
	else
		ft_error("Error\n");
	return (0);
}
