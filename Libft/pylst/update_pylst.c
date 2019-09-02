#include "libft.h"
#include <stdarg.h>

/*
** update_pylst:
**
** Arguments, in order :
** @pylst: choosen list.
** @index: index to modify.
** @value: value to change.
** @size: size of the new value.
** @ctype: C type of the new value.
**
** Facility to change an element of a specific index in a pylst.
** Is an equivalent in python to 'my_lst[x] = y'.
*/

void	update_pylst(t_pylst *pylst, int index, ...)
{
	va_list		args;
	void		*value;
	int			size;
	enum e_ctype	ctype;

	va_start(args, index);
	value = va_arg(args, void *);
	size = va_arg(args, int);
	ctype = va_arg(args, enum e_ctype);
	pylst = index_pylst(pylst, index);
	pylst_clean_node(pylst);
	if (size > 0)
	{
		pylst->value = ft_memalloc(size);
		ft_memcpy(pylst->value, value, size);
	}
	else
		pylst->value = value;
	pylst->size = size;
	pylst->ctype = ctype;
	va_end(args);
}
