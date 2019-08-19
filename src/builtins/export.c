#include "libft.h"
#include "tmpsh.h"

static void	show_exported_env(char **environ)
{
	char	*variable;
	char	*value;

	while (*environ)
	{
		variable = *environ;
		value = ft_strchr(*environ, "=");
		*value++ = '\0';
		if (ft_strlen(value) > 0)
			ft_printf("export %s=%s\n", variable, value);
		else
			ft_printf("export %s\n", variable);
		environ++;
	}
}

static int		manage_display(t_pylst *options, char **environ)
{
	t_pylst		*invalid_opt;

	if (options)
	{
		if (len_pylst(options) >= 2 || !ft_strequ(options->value, "p"))
		{
			invalid_opt = ft_strequ(options->value, "p") ?\
						  options->next : options;
			ft_printf("export: invalid option: %s\n", invalid_opt->value);
			free_pylst(&options, 0);
			return (1);
		}
	}
	free_pylst(&options, 0);
	show_exported_env(environ);
	return (0);
}

static void export_assignation(char *argument)
{
	char	*variable;
	char	*value;

	value = ft_strchr(argument, "=");
	*value++ = '\0';
	if (ft_strlen(variable) > 0)
	{
		if (ft_getvar(variable))
			ft_unsetvar(variable);
		ft_setenv(variable, value);
	}
}

static void		export_var(char *variable)
{
	char	*value;

	value = ft_getvar(variable);
	if (!value)
		value = "";
	ft_setvar(variable, value);
}

int		built_export(char **argv, char **environ)
{
	t_pylst		*options;
	int			argc;
	int			index;

	options = argparser(argv);
	if (len_pylst(options) > 0 || ft_arraylen(argv) == 0)
		return (manage_display(options, environ));
	index = 0;
	while (argv[index])
	{
		if (ft_strchr(argv[index], "="))
			export_assignation(argv[index]);
		else
			export_var(argv[index]);
		index++;
	}
	return (0);
}
