#include "libft.h"

/*
** str_in_pylst:
**
** Arguments, in order :
** @str: searched string.
** @pylst: choosen list.
**
** Return True if str is a value of pylst else return False.
** ! If str is founded pylst->iter_item is set to NULL !
*/

int		in_pylst_chare(char *str, t_pylst *pylst)
{
	char		*value;
	int			ret;

	ret = 0;
	while (iter_pylst(pylst, (void **)&value))
	{
		if (value && ft_strequ(str, value))
		{
			ret = 1;
			pylst->iter_item = NULL;
			break ;
		}
	}
	return (ret);
}
