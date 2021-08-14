#include "../push_swap.h"

t_List	*created_list(void)
{
	t_List	*tmp;

	tmp = (t_List *)malloc(sizeof(t_List));
	if (!tmp)
		ft_error("Malloc error\n");
	tmp->size = 0;
	tmp->head = NULL;
	tmp->tail = tmp->head;
	return (tmp);
}

void	pushFront(t_List *list, struct s_data data)
{
	t_Node	*tmp;

	tmp = (t_Node *)malloc(sizeof(t_Node));
	if (!tmp)
		exit(1);
	tmp->data = data;
	tmp->next = list->head;
	tmp->prev = NULL;
	if (list->head)
		list->head->prev = tmp;
	list->head = tmp;
	if (list->tail == NULL)
		list->tail = tmp;
	list->size++;
}

struct s_data	popFront(t_List *list)
{
	t_Node			*prev;
	struct s_data	tmp;

	if (list->head == NULL)
		exit(1);
	prev = list->head;
	list->head = list->head->next;
	if (list->head)
		list->head->prev = NULL;
	if (prev == list->tail)
		list->tail = NULL;
	tmp = prev->data;
	free(prev);
	list->size--;
	return (tmp);
}

void	pushBack(t_List *list, struct s_data data)
{
	t_Node	*tmp;

	tmp = (t_Node *)malloc(sizeof(t_Node));
	if (!tmp)
		ft_error("Malloc error\n");
	tmp->data = data;
	tmp->next = NULL;
	tmp->prev = list->tail;
	if (list->tail)
		list->tail->next = tmp;
	list->tail = tmp;
	if (list->head == NULL)
		list->head = tmp;
	list->size++;
}

struct s_data	popBack(t_List *list)
{
	t_Node			*next;
	struct s_data	tmp;

	if (list->tail == NULL)
		exit(1);
	next = list->tail;
	list->tail = list->tail->prev;
	if (list->tail)
		list->tail->next = NULL;
	if (next == list->head)
		list->head = NULL;
	tmp = next->data;
	free(next);
	list->size--;
	return (tmp);
}
