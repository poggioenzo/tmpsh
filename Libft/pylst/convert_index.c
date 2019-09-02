#include "libft.h"

/*
** convert_index:
**
** Whenever the user is given an negativ index, research his
** positiv relation.
*/

int		convert_index(t_pylst *pylst, int index)
{
	int		lst_len;

	if (index < 0)
	{
		lst_len = len_pylst(pylst);
		index = lst_len + index;
	}
	return (index);
}

