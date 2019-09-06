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

/*
** remove_all:
**
** Verify if we have the -a option.
** If it's the case, empty the shell hash table of alias.
** Display an error message if the option is invalid.
*/

static int		remove_all(t_pylst *options)
{
	t_pylst		*error_option;

	if (len_pylst(options) == 1 && ft_strequ(options->value, "a"))
	{
		free_pylst(&options, 0);
		empty_ht(g_alias);
		return (0);
	}
	error_option = options;
	while (error_option && ft_strequ(error_option->value, "a"))
		error_option = error_option->next;
	ft_dprintf(2, "unalias: bad option: %s\n", error_option->value);
	free_pylst(&options, 0);
	return (1);
}

/*
** built_unalias:
**
** unalias - remove alias definition.
**
** Synopsis : unalias alias-name [...]
**			  unalias -a
**
** Options:
** -a : Remove all alias definition.
*/

int				built_unalias(char **argv, NOT_USE(char **environ))
{
	t_pylst		*options;
	int			argc;
	int			index;

	argc = ft_arraylen(argv);
	if (argc == 0)
	{
		ft_dprintf(2, "unalias: not enough arguments.\n");
		return (1);
	}
	options = argparser(argv);
	if (len_pylst(options) >= 1)
		return (remove_all(options));
	index = 0;
	while (argv[index])
	{
		if (search_value(g_alias, argv[index]))
			delete_value(g_alias, argv[index]);
		else
			ft_printf("unalias: no such hash table element: %s\n",\
					argv[index]);
		index++;
	}
	return (0);
}
