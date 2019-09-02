#include "libft.h"

/*
** insert_sort_pylst:
**
** Utils for sort_pylst. Insert a new element inside a sorted list.
*/

static void	insert_sort_pylst(t_pylst **new_pylst, t_pylst *new_node, \
		int (*cmp)(t_pylst *, t_pylst *))
{
	t_pylst		*prev;
	t_pylst		*curr;

	prev = NULL;
	curr = *new_pylst;
	while (curr && cmp(curr, new_node) <= 0)
	{
		prev = curr;
		curr = curr->next;
	}
	if (!prev)
		*new_pylst = new_node;
	else
		prev->next = new_node;
	if (curr)
		new_node->next = curr;
}

/*
** sort_pylst:
**
** @pylst: list to sort.
** @cmp: Compare function to perform the sort
**
** Sort the given chained list by performing an insert sort.
*/

void		sort_pylst(t_pylst **pylst, int (*cmp)(t_pylst *, t_pylst *))
{
	t_pylst		*sorted_pylst;
	t_pylst		*to_sort;
	t_pylst		*next;

	sorted_pylst = NULL;
	to_sort = *pylst;
	while (to_sort)
	{
		next = to_sort->next;
		to_sort->next = NULL;
		insert_sort_pylst(&sorted_pylst, to_sort, cmp);
		to_sort = next;
	}
	*pylst = sorted_pylst;
}
