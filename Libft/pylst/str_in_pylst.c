#include "libft.h"

/*
** str_in_pylst:
**
** Check if the searched string is inside the list.
*/

int			str_in_pylst(t_pylst *pylst, char *search)
{
	char	*tmp_value;

	while (pylst)
	{
		tmp_value = (char *)pylst->value;
		if (ft_strequ(search, tmp_value))
			return (1);
		pylst = pylst->next;
	}
	return (0);
}
