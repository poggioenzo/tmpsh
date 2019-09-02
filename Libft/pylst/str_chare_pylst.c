#include "libft.h"

/*
** str_chare_pylst:
**
** Arguments, in order :
** @pylst: choosen list.
**
** Return a string of python'style list of pylst.
** ! Work only if pylst values are char * !
*/

char	*str_chare_pylst(t_pylst *pylst)
{
	char *str;
	char *cara;

	if (!pylst)
		return (ft_strdup("[]\n"));
	cara = "['";
	str = join_pylst(pylst, "', '");
	str = ft_fstrjoin(&cara, &str, FALSE, TRUE);
	cara = "']\n";
	str = ft_fstrjoin(&str, &cara, TRUE, FALSE);
	return (str);
}
