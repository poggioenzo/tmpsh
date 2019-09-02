#include "libft.h"

/*
** precedence_pylst:
**
** Get the t_pylst element just before the given index.
*/

t_pylst		*precedence_pylst(t_pylst *pylst, int index)
{
	index = convert_index(pylst, index);
	if (index == 0)
		return (NULL);
	return (index_pylst(pylst, index - 1));
}
