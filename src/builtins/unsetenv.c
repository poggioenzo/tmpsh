#include "environ_utils.h"
#include "libft.h"

/*
** unsetenv:
**
** Remove the given list of environnement variable.
** SYNTAX : unsetenv variable [variable ...]
*/

void	built_unsetenv(char **args)
{
	int		argc;
	int		index;

	argc = ft_arraylen(args);
	if (argc == 0)
		ft_dprintf(2, "unsetenv: Too few arguments.\n");
	else
	{
		index = 0;
		while (index < argc)
			ft_unsetenv(args[index++]);
	}
}
