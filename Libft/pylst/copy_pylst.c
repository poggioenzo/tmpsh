#include "libft.h"

/*
** pylst_deepcpy:
**
** Return a deep copy of the given t_pylst.
** Allocate new fresh node, and copy all possible
** value within a node.
*/

t_pylst		*pylst_deepcpy(t_pylst *pylst)
{
	return (slice_pylst(pylst, 0, len_pylst(pylst)));
}

/*
** pylst_shacpy:
**
** @pylst : t_pylst to copy.
**
** Return a shallow copy of the pylst.
** Juste allocate node of pylst.
**
** return : - Shallow copy of the list.
*/

t_pylst		*pylst_shacpy(t_pylst *pylst)
{
	t_pylst		*shallow_cpy;

	shallow_cpy = NULL;
	while (pylst)
	{
		push_pylst(&shallow_cpy, pylst->value, 0, pylst->ctype);
		pylst = pylst->next;
	}
	return (shallow_cpy);
}
