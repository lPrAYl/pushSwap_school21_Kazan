#include "../push_swap.h"

t_Node	*getNthq(t_List *list, size_t index)
{
	t_Node	*tmp;
	size_t	i;

	tmp = NULL;
	if (index < list->size / 2)
	{
		i = 0;
		tmp = list->head;
		while (tmp && i < index)
		{
			tmp = tmp->next;
			i++;
		}
	}
	else
	{
		i = list->size - 1;
		tmp = list->tail;
		while (tmp && i > index)
		{
			tmp = tmp->prev;
			i--;
		}
	}
	return (tmp);
}

void	insert(t_List *list, size_t index, struct s_data data)
{
	t_Node	*elm;
	t_Node	*ins;

	elm = NULL;
	ins = NULL;
	elm = getNthq(list, index);
	if (elm == NULL)
		exit(1);
	ins = (t_Node *)malloc(sizeof(t_Node));
	if (ins == NULL)
		exit(1);
	ins->data = data;
	ins->prev = elm;
	ins->next = elm->next;
	if (elm->next)
	{
		elm->next->prev = ins;
	}
	elm->next = ins;
	if (!elm->prev)
		list->head = elm;
	if (!elm->next)
		list->tail = elm;
	list->size++;
}

struct s_data	deleteNth(t_List *list, size_t index)
{
	t_Node	*elm;
	t_data	tmp;

	elm = NULL;
	elm = getNthq(list, index);
	if (elm == NULL)
		exit(1);
	if (elm->prev)
		elm->prev->next = elm->next;
	if (elm->next)
		elm->next->prev = elm->prev;
	tmp = elm->data;
	if (!elm->prev)
		list->head = elm->next;
	if (!elm->next)
		list->tail = elm->prev;
	free(elm);
	list->size--;
	return (tmp);
}

void	print_List(t_List *list)
{
	t_Node	*tmp;

	tmp = list->head;
	ft_printf("value\t");
	ft_printf("pos\t");
	ft_printf("index\t");
	ft_printf("keep\n");
	while (tmp)
	{
		ft_printf("%5d ", tmp->data.value);
		ft_printf("%5d ", tmp->data.pos_in_stk);
		ft_printf("%5d ", tmp->data.index);
		ft_printf("%5d\n", tmp->data.keep_in_stk);
		tmp = tmp->next;
	}
	ft_printf("\n");
}

void	delete_List(t_List **list)
{
	t_Node	*tmp;
	t_Node	*next;

	tmp = (*list)->head;
	next = NULL;
	while (tmp)
	{
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
	free(*list);
	(*list) = NULL;
}
