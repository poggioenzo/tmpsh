#include "libft.h"
#include "tmpsh.h"
#include "variables.h"

int		built_unsetenv(char **argv, char **environ)
{
	int		index;

	UNUSED(environ);
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

static int		show_environ(char **environ)
{
	int		index;

	index = 0;
	while (environ[index])
		ft_printf("%s\n", environ[index++]);
	return (0);
}

int		built_setenv(char **argv, char **environ)
{
	int		index;
	char	*variable;
	char	*value;

	UNUSED(environ);
	if (ft_arraylen(argv) == 0)
		return (show_environ(environ));
	index = 0;
	while (argv[index])
	{
		if ((value = ft_strchr(argv[index], "=")))
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
