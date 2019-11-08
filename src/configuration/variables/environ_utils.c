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

#include "environ_utils.h"
#include "tmpsh.h"
#include "libft.h"

/*
** ft_getenv_index:
**
** Get the index in the environnement list of the given variable.
*/

int				ft_getenv_index(char *variable, char **environ)
{
	int		index;
	int		len_var;

	index = 0;
	len_var = ft_strlen(variable);
	while (environ[index])
	{
		if (ft_start_with(environ[index], variable) \
				&& environ[index][len_var] == '=')
			return (index);
		index++;
	}
	return (-1);
}

/*
** ft_getenv:
**
** Kind of getenv but for a specified environnement.
*/

char			*ft_getenv_common(char *variable, char **environ)
{
	int		index;
	int		len_var;

	len_var = ft_strlen(variable);
	if ((index = ft_getenv_index(variable, environ)) >= 0)
		return (environ[index] + len_var + 1);
	return (NULL);
}

/*
** format_env_variable:
**
** From a given variable name and his value, format the string in the
** environnement format, like variable=value.
*/

char			*format_env_variable(char *variable, char *value)
{
	char	*format_env;
	int		len_var;
	int		len_val;

	len_var = ft_strlen(variable);
	len_val = ft_strlen(value);
	format_env = ft_memalloc(sizeof(char) * (len_var + len_val + 2));
	ft_strcpy(format_env, variable);
	format_env[len_var] = '=';
	ft_strcpy(format_env + len_var + 1, value);
	return (format_env);
}
