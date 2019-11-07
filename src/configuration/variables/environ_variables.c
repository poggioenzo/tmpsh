/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   environ_variables.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: simrossi <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/07 10:35:22 by simrossi     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/07 11:01:54 by simrossi    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "tmpsh.h"
#include "variables.h"

/*
** ft_getenv:
**
** Behave like getenv but for the local environnement.
*/

char		*ft_getenv(char *variable)
{
	return (ft_getenv_common(variable, g_environ));
}

/*
** ft_unsetenv:
**
** Remove a variable from the environnement
*/

void			ft_unsetenv(char *variable)
{
	int		index;

	index = ft_getenv_index(variable, g_environ);
	if (index >= 0)
		ft_array_remove(g_environ, g_environ[index], TRUE);
}

/*
** ft_setenv:
**
** Add or update the value of a environnement variable
*/

void			ft_setenv(char *variable, char *value)
{
	int		index;
	char	*format_env;

	format_env = format_env_variable(variable, value);
	index = ft_getenv_index(variable, g_environ);
	if (index >= 0)
	{
		FREE(g_environ[index]);
		g_environ[index] = format_env;
	}
	else
		g_environ = ft_array_extend(g_environ, format_env, FALSE);
}
