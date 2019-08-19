#include "libft.h"
#include "tmpsh.h"
#include "variables.h"

int		built_unset(char **argv, char **environ)
{
	int		index;

	UNUSED(environ);
	index = 0;
	while (argv[index])
	{
		if (ft_getvar(argv[index]))
			ft_unsetvar(argv[index]);
		else
			ft_printf("unset: unknow variable: %s\n", argv[index]);
		index++;
	}
	return (0);
}

static int		show_variables(void)
{
	char	*variable;
	char	*value;

	while (ht_iter(g_variables, &variable, &value))
		ft_printf("%s=%s\n", variable, value);
	return (0);
}

int		built_set(char **argv, char **environ)
{
	int		index;
	char	*equal;
	char	*variable;
	char	*value;

	UNUSED(environ);
	if (ft_arraylen(argv) == 0)
		return (show_variables());
	index = 0;
	while (argv[index])
	{
		if ((equal = ft_strchr(argv[index], "=")))
		{
			*equal = '\0';
			variable = argv[index];
			value = equal + 1;
			if (ft_strlen(variable) > 0)
				ft_setvar(variable, value);
		}
		index++;
	}
	return (0);
}
