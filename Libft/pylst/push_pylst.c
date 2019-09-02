#include "libft.h"

/*
** alloc_pylst_node:
**
** Allocate a single t_pylst * (aka struct s_pylst *) element.
** Duplicate his value content if the size is given.
*/

static void		alloc_pylst_node(t_pylst **py_node, void *value, int size, \
		int ctype)
{
	*py_node = (t_pylst *)ft_memalloc(sizeof(t_pylst));
	if (size > 0)
	{
		(*py_node)->value = ft_memalloc(size);
		ft_memcpy((*py_node)->value, value, size);
	}
	else
		(*py_node)->value = value;
	(*py_node)->ctype = ctype;
	(*py_node)->size = size;
	(*py_node)->next = NULL;
	(*py_node)->iter_item = NULL;
}

/*
** push_pylst:
**
** Push at the end of the current list a new element.
** Copy the given value if a size is given.
*/

void			push_pylst(t_pylst **pylst, void *value, int size, int ctype)
{
	if (!*pylst)
		alloc_pylst_node(pylst, value, size, ctype);
	else
	{
		while ((*pylst)->next)
			pylst = &(*pylst)->next;
		alloc_pylst_node(&(*pylst)->next, value, size, ctype);
	}
}
