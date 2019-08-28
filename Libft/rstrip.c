#include "libft.h"

/*
** rstrip:
**
** Remove all newline at the end of the string.
*/

void		rstrip(char *str)
{
	int		index;

	index = ft_strlen(str) - 1;
	while (index >= 0 && str[index] == '\n')
		str[index--] = '\0';
}
