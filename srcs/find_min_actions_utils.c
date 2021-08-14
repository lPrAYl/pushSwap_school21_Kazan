#include "../push_swap.h"

static t_opt	fill_case_one(t_opt current_actions, int case_one)
{
	t_opt	actions;

	actions = init_actions();
	actions.total = case_one;
	if (case_one == current_actions.ra)
	{
		actions.rr = current_actions.rb;
		actions.ra = current_actions.ra - current_actions.rb;
	}
	else
	{
		actions.rr = current_actions.ra;
		actions.rb = current_actions.rb - current_actions.ra;
	}
	return (actions);
}

static t_opt	fill_case_two(t_opt current_actions, int case_two)
{
	t_opt	actions;

	actions = init_actions();
	actions.total = case_two;
	if (case_two == -current_actions.rra)
	{
		actions.rrr = -current_actions.rrb;
		actions.rra = -(current_actions.rra - current_actions.rrb);
	}
	else
	{
		actions.rrr = -current_actions.rra;
		actions.rrb = -(current_actions.rrb - current_actions.rra);
	}
	return (actions);
}

static t_opt	fill_case_three(t_opt current_actions, int case_three)
{
	t_opt	actions;

	actions = init_actions();
	actions.total = case_three;
	actions.ra = current_actions.ra;
	actions.rrb = -current_actions.rrb;
	return (actions);
}

static t_opt	fill_case_four(t_opt current_actions, int case_four)
{
	t_opt	actions;

	actions = init_actions();
	actions.total = case_four;
	actions.rb = current_actions.rb;
	actions.rra = -current_actions.rra;
	return (actions);
}

void	find_count_actions(t_opt *actions)
{
	int	case_one;
	int	case_two;
	int	case_three;
	int	case_four;

	case_one = ft_max((*actions).ra, (*actions).rb);
	case_two = ft_max(-(*actions).rra, -(*actions).rrb);
	case_three = (*actions).ra - (*actions).rrb;
	case_four = (*actions).rb - (*actions).rra;
	if (case_one < (*actions).total && case_one <= case_two
		&& case_one <= case_three && case_one <= case_four)
		*actions = fill_case_one(*actions, case_one);
	else if (case_two < (*actions).total && case_two < case_one
		&& case_two <= case_three && case_two <= case_four)
		*actions = fill_case_two(*actions, case_two);
	else if (case_three < (*actions).total && case_three < case_one
		&& case_three < case_two && case_three <= case_four)
		*actions = fill_case_three(*actions, case_three);
	else if (case_four < (*actions).total && case_four < case_one
		&& case_four < case_two && case_four < case_three)
		*actions = fill_case_four(*actions, case_four);
}
