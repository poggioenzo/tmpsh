#include "libft.h"

/*
** built_exit:
**
** exit - quit the current shell process
**
** Synopsis : exit [n]
*/

int		built_exit(char **args, char **env)
{
	int		argc;
	int		value;

	UNUSED(env);
	argc = ft_arraylen(args);
	if (argc > 2)
	{
		ft_dprintf(2, "exit: too many arguments\n");
		return (1);
	}
	else if (argc == 1)
		value = ft_atoi(args[0]);
	else
		value = 0;
	exit(value);
}
