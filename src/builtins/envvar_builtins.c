#include "libft.h"
#include "tmpsh.h"
#include "variables.h"

/*
** built_unsetenv:
**
** unsetenv - remove variables from the environnement.
**
** Synopsis : unsetenv [variable ... ]
*/

int				built_unsetenv(char **argv, NOT_USE(char **environ))
{
	int		index;

	if (ft_arraylen(argv) == 0)
	{
		ft_dprintf(2, "unsetenv: no arguments.\n");
		return (1);
	}
	index = 0;
	while (argv[index])
	{
		if (ft_getenv(argv[index]))
			ft_unsetenv(argv[index]);
		else
			ft_printf("unsetenv: unknow variable: %s\n",\
					argv[index]);
		index++;
	}
	return (0);
}

/*
** show_environ:
**
** Display the given environnement to stdout.
*/

static int		show_environ(char **environ)
{
	int		index;

	index = 0;
	while (environ[index])
		ft_printf("%s\n", environ[index++]);
	return (0);
}

/*
** built_setenv:
**
** setenv - set or display environmment variables.
**
** Synopsis: setenv [variable=value ...]
**
** If no argument is given, display the entire environnement.
** Otherwise, et each given variable assignation to the environnement.
*/

int				built_setenv(char **argv, char **environ)
{
	int		index;
	char	*variable;
	char	*value;

	if (ft_arraylen(argv) == 0)
		return (show_environ(environ));
	index = 0;
	while (argv[index])
	{
		if ((value = ft_strchr(argv[index], '=')))
		{
			*value++ = '\0';
			variable = argv[index];
			if (ft_strlen(variable) > 0)
				ft_setenv(variable, value);
		}
		index++;
	}
	return (0);
}
