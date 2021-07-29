#include "../push_swap.h"

	//	создание кольцевого двусвязного списка

Ring	*createRing()
{
	Ring	*tmp;
	
	tmp = (Ring *)malloc(sizeof(Ring));
	if (!tmp)
		ft_error("Error malloc\n");
	tmp->size = 0;
	tmp->current = NULL;
	return (tmp);
}

	//	добавление элементов в список

void	addElem(Ring *ring, struct s_data data)
{
	Node	*prev;
	Node	*tmp;
	
	prev = NULL;
	tmp = (Node *)malloc(sizeof(Node));
	tmp->data = data;
	if (ring->current == NULL)
	{
		ring->current = tmp;
		tmp->next = tmp->prev = tmp;
	}
	else
	{
		prev = ring->current->next->prev;
		tmp->next = ring->current->next;
		tmp->prev = ring->current;
		prev->prev = tmp;
		ring->current->next = tmp;
		ring->current = tmp;
	}
	ring->size++;
}

	//	удаление элемента из списка и возвращение его значения

struct s_data	removeElem(Ring *ring)
{
	Node			*afterTarget;
	struct s_data	retVal;
	
	if (ring->current == NULL)
		exit(1);
	if (ring->current->next == ring->current)
	{
		retVal = ring->current->data;
		free(ring->current);
		ring->current = NULL;
	}
	else
	{
		afterTarget = ring->current->next;
		ring->current->prev->next = afterTarget;
		afterTarget->prev = ring->current->prev;
		retVal = ring->current->data;
		free(ring->current);
		ring->current = afterTarget;
	}
	ring->size--;
	return (retVal);
}

Node	*next(Ring *ring)
{
	Node	*retVal;
	
	retVal = NULL;
	if (ring->current)
	{
		ring->current = ring->current->next;
		retVal = ring->current;
	}
	return (retVal);
}

Node	*prev(Ring *ring)
{
	Node	*retVal = NULL;
	if (ring->current)
	{
		ring->current = ring->current->prev;
		retVal = ring->current;
	}
	return (retVal);
}

