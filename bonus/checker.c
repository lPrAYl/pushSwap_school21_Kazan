#include "checker.h"

static void	read_cmd(t_List **stkA, t_List **stkB, char *line)
{
	if (!ft_strncmp(line, "sa", 3))
		swap(stkA, NULL, 'a', 'n');
	else if (!ft_strncmp(line, "sb", 3))
		swap(NULL, stkB, 'b', 'n');
	else if (!ft_strncmp(line, "ss", 3))
		swap(stkA, stkB, 's', 'n');
	else if (!ft_strncmp(line, "pa", 3))
		push(stkA, stkB, 'a', 'n');
	else if (!ft_strncmp(line, "pb", 3))
		push(stkA, stkB, 'b', 'n');
	else if (!ft_strncmp(line, "ra", 3))
		rotate(stkA, NULL, 'a', 'n');
	else if (!ft_strncmp(line, "rb", 3))
		rotate(NULL, stkB, 'b', 'n');
	else if (!ft_strncmp(line, "rr", 3))
		rotate(stkA, stkB, 's', 'n');
	else if (!ft_strncmp(line, "rra", 4))
		rev_rotate(stkA, NULL, 'a', 'n');
	else if (!ft_strncmp(line, "rrb", 4))
		rev_rotate(NULL, stkB, 'b', 'n');
	else if (!ft_strncmp(line, "rrr", 3))
		rev_rotate(stkA, stkB, 's', 'n');
	else
		ft_error("Error\n");
}

int	main(int argc, char **argv)
{
	char	*line;
	t_List	*stkA;
	t_List	*stkB;

	if (argc > 1)
	{
		stkA = validate_data(argv);
		stkB = created_list();
		while (get_next_line(0, &line))
		{
			read_cmd(&stkA, &stkB, line);
			free(line);
		}
		if (check_sorting(stkA) && stkB->size == 0)
			ft_putstr_fd("OK\n", 1);
		else
			ft_putstr_fd("KO\n", 1);
	}
	else
		ft_error("Error\n");
}
