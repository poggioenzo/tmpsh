#include "libft.h"

/*
** print_pylst_chare:
**
** Arguments, in order :
** @pylst: choosen list.
**
** Print a python'style list of string.
** ! Work only if pylst values are char * !
*/

void	print_pylst_chare(t_pylst *pylst)
{
	if (!(pylst))
	{
		ft_printf("Empty list.\n");
		return ;
	}
	ft_printf(str_chare_pylst(pylst));
}
