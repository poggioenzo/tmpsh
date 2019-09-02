#include "libft.h"

/*
** len_pylst:
**
** Return the total length of the given list.
*/

int			len_pylst(t_pylst *pylst)
{
	int		size;

	size = 0;
	while (pylst)
	{
		pylst = pylst->next;
		size++;
	}
	return (size);
}
