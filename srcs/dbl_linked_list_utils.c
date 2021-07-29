#include "../push_swap.h"

DblLinkedList	*createDblLinkedList()
{
	DblLinkedList	*tmp;
	
	tmp = (DblLinkedList *)malloc(sizeof(DblLinkedList));
	if (!tmp)
		ft_error("Malloc error\n");
	tmp->size = 0;
	tmp->head = NULL;
	tmp->tail = tmp->head;
	return (tmp);
}

void	deleteDblLinkedList(DblLinkedList **list)
{
	Node	*tmp;
	Node	*next;
	
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

void	pushFront(DblLinkedList *list, struct s_data data)
{
	Node	*tmp;
	
	tmp = (Node *)malloc(sizeof(Node));
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

struct s_data	popFront(DblLinkedList *list)
{
	Node			*prev;
	struct s_data	tmp;
	
	if (list->head == NULL)
		exit(1);
	prev = list->head;
	list->head = list->head->next;
	if (list->head)
		list->head->prev = NULL;
	if (prev == list->tail)
		list->tail =NULL;
	tmp = prev->data;
	free(prev);
	list->size--;
	return (tmp);
}

void	pushBack(DblLinkedList *list, struct s_data data)
{
	Node	*tmp;
	
	tmp = (Node *)malloc(sizeof(Node));
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

struct s_data	popBack(DblLinkedList *list)
{
	Node			*next;
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

Node	*getNth(DblLinkedList *list, size_t index)
{
	Node	*tmp;
	size_t	i;
	
	i = 0;
	tmp = list->head;
	while (tmp && i < index)
	{
		tmp = tmp->next;
		i++;
	}
	return (tmp);
}


Node	*getNthq(DblLinkedList *list, size_t index)
{
	Node	*tmp;
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


void	insert(DblLinkedList *list, size_t index, struct s_data data)
{
	Node *elm;
	Node *ins;
	
	elm = NULL;
	ins = NULL;
	elm = getNth(list, index);
	if (elm == NULL)
		exit(1);
	ins = (Node*) malloc(sizeof(Node));
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

struct s_data	deleteNth(DblLinkedList *list, size_t index)
{
	Node 			*elm;
	struct s_data	tmp;
	
	elm = NULL;
	elm = getNth(list, index);
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


void	printInt(struct s_data data)
{
	ft_printf("%d ", data.value);
}

void	printDblLinkedList(DblLinkedList *list)
{
	Node *tmp;
	
	tmp = list->head;
	ft_printf("value\t");
	ft_printf("pos\t");
	ft_printf("index\t");
	ft_printf("keep\n");
	while (tmp)
	{
		ft_printf("%5d ", tmp->data.value);
		ft_printf("%5d ", tmp->data.pos_in_stack);
		ft_printf("%5d ", tmp->data.index);
		ft_printf("%5d\n", tmp->data.keep_in_stack);
		tmp = tmp->next;
	}
	ft_printf("\n");
}


//DblLinkedList	*fromArray(void *arr, size_t n, size_t size)
//{
//	DblLinkedList	*tmp;
//	size_t			i;
//
//	tmp = NULL;
//	i = 0;
//	if (arr == NULL)
//		exit(1);
//	tmp = createDblLinkedList();
//	while (i < n)
//	{
//
//		pushBack(tmp, ((char*)arr + i * size));
//		i++;
//	}
//	return (tmp);
//}


//int	main(void)
//{
//	DblLinkedList *list = createDblLinkedList();
//	int a, b, c, d, e, f, g, h;
//
//	a = 10;
//	b = 20;
//	c = 30;
//	d = 40;
//	e = 50;
//	f = 60;
//	g = 70;
//	h = 80;
//	pushBack(list, &a);
//	pushFront(list, &b);
//	pushFront(list, &c);
//	pushBack(list, &d);
//	pushBack(list, &e);
//	pushBack(list, &f);
//	printDblLinkedList(list, printInt);
//	ft_printf("length %d\n", list->size);
//	ft_printf("nth 2 %d\n", *((int*)(getNthq(list, 2))->data));
//	ft_printf("nth 5 %d\n", *((int*)(getNthq(list, 5))->data));
//	ft_printf("popFront %d\n", *((int*)popFront(list)));
//	ft_printf("popFront %d\n", *((int*)popFront(list)));
//	ft_printf("head %d\n", *((int*)(list->head->data)));
//	ft_printf("tail %d\n", *((int*)(list->tail->data)));
//	ft_printf("popBack %d\n", *((int*)popBack(list)));
//	ft_printf("popBack %d\n", *((int*)popBack(list)));
//	ft_printf("length %d\n", list->size);
//	printDblLinkedList(list, printInt);
//	insert(list, 1, &g);
//	printDblLinkedList(list, printInt);
//	deleteNth(list, 0);
//	printDblLinkedList(list, printInt);
//	deleteDblLinkedList(&list);
//}

