#include "libft.h"
#include "tmpsh.h"
#include "variables.h"
#include "argparser.h"

/*
** show_exported_env:
**
** Print to stdout each exported variable,
** in the POSIX format.
*/

static void	show_exported_env(char **environ)
{
	char	*variable;
	char	*value;

	while (*environ)
	{
		variable = *environ;
		value = ft_strchr(*environ, '=');
		*value++ = '\0';
		if (ft_strlen(value) > 0)
			ft_printf("export %s=%s\n", variable, value);
		else
			ft_printf("export %s\n", variable);
		environ++;
	}
}

/*
** manage_display:
**
** Check if we have the -p option.
** In this case, display the exported environnement.
** Display an error message if an error occur.
*/

static int		manage_display(t_pylst *options, char **environ)
{
	t_pylst		*invalid_opt;

	if (options)
	{
		if (len_pylst(options) >= 2 || !ft_strequ(options->value, "p"))
		{
			invalid_opt = ft_strequ(options->value, "p") ?\
						  options->next : options;
			ft_dprintf(2, "export: invalid option: %s\n", invalid_opt->value);
			free_pylst(&options, 0);
			return (1);
		}
	}
	free_pylst(&options, 0);
	show_exported_env(environ);
	return (0);
}

/*
** export_assignation:
**
** @argument: single assignation to export.
**
** Perform an export of the given variable and his value.
** If the variable already exists in the local environnement,
** remove it.
*/

static void export_assignation(char *argument)
{
	char	*variable;
	char	*value;

	value = ft_strchr(argument, '=');
	variable = argument;
	*value++ = '\0';
	if (ft_strlen(variable) > 0)
	{
		if (ft_getvar(variable))
			ft_unsetvar(variable);
		ft_setenv(variable, value);
	}
}

/*
** export_var:
**
** Verify if the given variable already exist,
** and set it to the environnement.
** If the variable do not exist, set an empty string
** as value.
*/

static void		export_var(char *variable)
{
	char	*value;

	value = ft_getvar(variable);
	if (!value)
		value = "";
	ft_setvar(variable, value);
}

/*
** built_export:
**
** export - set variable to the environnement.
**
** Synopsis: export name[=word]...
**			 export -p
**
** Options:
** -p : print to stdout name and value of exported
**		environnement.
*/

int		built_export(char **argv, char **environ)
{
	t_pylst		*options;
	int			index;

	options = argparser(argv);
	if (len_pylst(options) > 0 || ft_arraylen(argv) == 0)
		return (manage_display(options, environ));
	index = 0;
	while (argv[index])
	{
		if (ft_strchr(argv[index], '='))
			export_assignation(argv[index]);
		else
			export_var(argv[index]);
		index++;
	}
	return (0);
}
