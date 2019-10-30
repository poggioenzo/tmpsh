/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   determine_bytes.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: simrossi <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/27 15:04:52 by simrossi     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/30 15:43:28 by simrossi    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"
#include "tmpsh.h"
#include "exec_file.h"
#include "argparser.h"

/*
** error_options:
**
** Display an error message if there is any option.
*/

static int		error_options(char **argv)
{
	t_pylst		*options;

	options = argparser(argv);
	if (len_pylst(options) > 0)
	{
		ft_dprintf(2, "type: invalid option: %s\n", options->value);
		return (free_pylst(&options, true));
	}
	return (false);
}

/*
** built_type:
**
** type - write a description of command type
**
** Synopsis : type name [...]
**
** Display how name will be interpreted by the
** shell.
**
** Methods:
** - name is a builtin.
** - name is an alias.
** - name is cached command, in hash table.
** - name is a command, searched with PATH.
** - name is an executable file.
**
** output : - absolute filename of the command.
**			- description of the method if no file exist.
**			- error message.
*/

int				built_type(char **argv, NOT_USE(char **environ))
{
	char	*used_elem;
	int		status;

	if (error_options(argv) == true)
		return (1);
	status = 0;
	while (*argv)
	{
		if ((used_elem = search_value(g_hash, *argv)))
			ft_printf("%s\n", ((t_hash_exec *)used_elem)->exec_file);
		else if ((used_elem = search_value(g_alias, *argv)))
			ft_printf("%s is aliased to '%s'\n", *argv, used_elem);
		else if ((search_value(g_builtins, *argv)))
			ft_printf("%s is a shell builtin\n", *argv);
		else if ((used_elem = get_execname(*argv, false)))
			ft_printf("%s\n", used_elem);
		else
		{
			ft_printf("type: %s: not found\n", *argv);
			status = 1;
		}
		argv++;
	}
	return (status);
}
