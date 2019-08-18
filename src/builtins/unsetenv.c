#include "environ_utils.h"
#include "libft.h"

/*
** unsetenv:
**
** Remove the given list of environnement variable.
** SYNTAX : unsetenv variable [variable ...]
*/

int		built_unsetenv(char **args, char **env)
{
	int		argc;
	int		index;

	UNUSED(env);
	argc = ft_arraylen(args);
	if (argc == 0)
	{
		ft_dprintf(2, "unsetenv: Too few arguments.\n");
		return (1);
	}
	else
	{
		index = 0;
		while (index < argc)
			ft_unsetenv(args[index++]);
	}
	return (0);
}
