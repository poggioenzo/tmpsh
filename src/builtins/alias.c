/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   determine_bytes.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: simrossi <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/27 15:04:52 by simrossi     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/27 15:04:55 by simrossi    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"
#include "tmpsh.h"
#include "argparser.h"

t_ht_table		*g_alias = NULL;

/*
** error_args:
**
** Check if there is any options in argv,
** and display an error message if any because
** alias do not have options.
*/

static t_bool		error_args(char **argv)
{
	t_pylst		*options;
	char		*error_opt;
	int			is_error;

	options = argparser(argv);
	is_error = len_pylst(options);
	if (is_error)
	{
		error_opt = options->value;
		ft_printf("alias: bad option: %s\n", error_opt);
	}
	free_pylst(&options, 0);
	return (is_error);
}

/*
** show_alias:
**
** Display all alias on stdout. Go trough the hash table of alias
** and print them in the posix format : "%s=%s\n".
*/

static int			show_alias(void)
{
	char	*alias;
	char	*value;

	while (ht_iter(g_alias, &alias, (void **)&value))
		ft_printf("%s='%s'\n", alias, value);
	return (0);
}

/*
** set_alias:
**
** Register the new alias inside the alias hash table.
** Starting from a string in the format "alias=value",
** separate the alias and the value to store it.
*/

static int			set_alias(char *argument)
{
	char	*equal;
	char	*alias;
	char	*value;

	equal = ft_strchr(argument, '=');
	*equal = '\0';
	alias = argument;
	value = equal + 1;
	if (ft_strlen(alias) == 0)
	{
		ft_dprintf(2, NAME_SH" alias: no alias name\n");
		return (1);
	}
	value = ft_strdup(value);
	insert_value(g_alias, alias, value, _chare);
	return (0);
}

/*
** built_alias:
**
** alias - Create, redefine or display aliases.
**
** Synopsis : alias [alias-name[=string]...]
**
** The following operands are supported:
**
** alias-name
**    Write the alias definition to standard output.
** alias-name=string
**    Assign the value of string to the alias alias-name.
**
** If no operands are given, all alias definitions
** are written to standard output.
*/

int					built_alias(char **argv, NOT_USE(char **environ))
{
	int		argc;
	int		index;
	char	*argument;
	char	*arg_value;

	if (error_args(argv) == true)
		return (1);
	if ((argc = ft_arraylen(argv)) == 0)
		return (show_alias());
	index = 0;
	while (index < argc)
	{
		argument = argv[index++];
		if (!ft_strchr(argument, '='))
		{
			if ((arg_value = search_value(g_alias, argument)))
				ft_printf("%s='%s'\n", argument, arg_value);
		}
		else
		{
			if (set_alias(argument) == 1)
				return (1);
		}
	}
	return (0);
}
