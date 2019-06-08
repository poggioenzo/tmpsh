#include "libft.h"

int		ft_array_in(char **array, char *string)
{
	while (*array)
	{
		if (ft_strequ(*array, string))
			return (1);
		array++;
	}
	return (0);
}
