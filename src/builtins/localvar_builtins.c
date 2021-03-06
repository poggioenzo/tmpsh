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
#include "variables.h"

/*
** built_unset:
**
** unset - remove local or environnement variable.
**
** Synopsis : unset [-v] name [...]
**
** Options:
** -v : remove alse environnement variables.
*/

int			built_unset(char **argv, char **environ)
{
	int		index;
	int		rm_env;
	int		status;

	status = 0;
	if (ft_arraylen(argv) == 0)
	{
		ft_dprintf(2, "unset: not enough arguments.\n");
		return (1);
	}
	rm_env = *argv && ft_strequ(*argv, "-v");
	index = rm_env;
	while (argv[index])
	{
		if (rm_env && ft_getenv_common(argv[index], environ))
			ft_unsetenv(argv[index]);
		else if (ft_getvar(argv[index]))
			ft_unsetvar(argv[index]);
		else if ((status = 1))
			ft_dprintf(2, "unset: unknow variable: %s\n", argv[index]);
		index++;
	}
	return (status);
}

/*
** show_variables:
**
** Print local variables in the POSIX format.
*/

static int	show_variables(void)
{
	char	*variable;
	char	*value;

	while (ht_iter(g_variables, &variable, (void **)&value))
		ft_printf("%s=%s\n", variable, value);
	return (0);
}

/*
** built_set:
**
** set - set or display local variables.
**
** Synopsis: set [name=value ...]
**
** Set each given name to the local variable set.
** If no argument is given, display all local
** variables.
*/

int			built_set(char **argv, NOT_USE(char **environ))
{
	int		index;
	char	*equal;
	char	*variable;
	char	*value;

	if (ft_arraylen(argv) == 0)
		return (show_variables());
	index = 0;
	while (argv[index])
	{
		if ((equal = ft_strchr(argv[index], '=')))
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
