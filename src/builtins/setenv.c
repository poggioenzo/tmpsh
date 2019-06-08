#include "tmpsh.h"
#include "environ_utils.h"
#include "libft.h"

static void		display_env(void)
{
	int		index;

	index = 0;
	while (g_environ[index])
		ft_printf("%s\n", g_environ[index++]);
}

/*
** setenv:
**
** Add to the environnement the given variable name
** and value.
** SYNTAX : setenv variable value
*/

void	built_setenv(char **args)
{
	int		argc;

	argc = ft_arraylen(args);
	if (argc > 2)
	{
		ft_dprintf(2, "setenv: Too many arguments.");
		return ;
	}
	else if (argc == 0)
		display_env();
	else
		ft_setenv(args[0], args[1]);
}
