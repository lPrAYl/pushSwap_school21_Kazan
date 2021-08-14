#include "../push_swap.h"

/**************** Сhecking string elements for validity ****************/

static void	ft_check_chunk(char *str)
{
	int	i;

	i = 0;
	if ((ft_strncmp(str, "2147483647", 10) > 0 && ft_strlen(str) == 10)
		|| (ft_strncmp(str, "-2147483648", 11) > 0 && ft_strlen(str) == 11)
		|| (ft_strncmp(str, "+2147483647", 12) > 0 && ft_strlen(str) == 12))
		ft_error("Overflow int\n");
	while (str[i])
	{
		if (i == 0 && (str[i] == '-' || str[i] == '+') && str[i + 1]
			&& ft_isdigit(str[i + 1]))
			i += 2;
		else if (ft_isdigit(str[i]))
			i++;
		else
			ft_error("Error\n");
	}
}

/**************** Initialization of each element of the list ****************/

static t_data	init_data(char *str)
{
	t_data	data;

	data.value = ft_atoi(str);
	data.pos_in_stk = -1;
	data.index = -1;
	data.keep_in_stk = 0;
	return (data);
}

/*********** Separating string elements with spaces, checking 
 * 				for validity of string elements, adding elements to a list,
 * 										checking for duplicates ***********/

t_List	*validate_data(char **argv)
{
	int		i;
	int		j;
	char	**chunk;
	t_List	*stk;
	t_data	data;

	i = 0;
	stk = created_list();
	while (argv[++i])
	{
		if (ft_strlen(argv[i]) == 0)
			ft_error("Error\n");
		j = -1;
		chunk = ft_split(argv[i], ' ');
		while (chunk[++j])
		{
			ft_check_chunk(chunk[j]);
			data = init_data(chunk[j]);
			pushBack(stk, data);
			free(chunk[j]);
		}
		free(chunk);
	}
	check_dup_and_index(stk, 0);
	return (stk);
}
