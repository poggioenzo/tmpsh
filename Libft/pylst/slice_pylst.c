#include "libft.h"

/*
** slice_pylst:
**
** Return a new allocated portion of the given list in the
** interval [from:to[.
**
** Allow negative number, -1 for the last node, etc.
*/

t_pylst		*slice_pylst(t_pylst *pylst, int from, int to)
{
	t_pylst		*start_node;
	t_pylst		*end_node;
	t_pylst		*sliced;

	sliced = NULL;
	start_node = index_pylst(pylst, from);
	end_node = index_pylst(pylst, to);
	if (start_node == end_node)
		return (NULL);
	while (1)
	{
		push_pylst(&sliced, start_node->value, start_node->size, \
				start_node->ctype);
		if (start_node->next == end_node)
			break ;
		start_node = start_node->next;
	}
	return (sliced);
}
