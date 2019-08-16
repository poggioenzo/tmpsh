#include "environ_utils.h"
#include "tmpsh.h"
#include "libft.h"

/*
** ft_getenv_index:
**
** Get the index in the environnement list of the given variable.
*/

static int		ft_getenv_index(char *variable)
{
	int		index;
	int		len_var;

	index = 0;
	len_var = ft_strlen(variable);
	while (g_environ[index])
	{
		if (ft_start_with(g_environ[index], variable) \
				&& g_environ[index][len_var] == '=')
			return (index);
		index++;
	}
	return (-1);
}

/*
** ft_getenv:
**
** Behave like getenv but for the local environnement.
*/

char			*ft_getenv(char *variable)
{
	int		index;
	int		len_var;

	len_var = ft_strlen(variable);
	if ((index = ft_getenv_index(variable)) >= 0)
		return (g_environ[index] + len_var + 1);
	return (NULL);
}

/*
** format_env_variable:
**
** From a given variable name and his value, format the string in the
** environnement format, like variable=value.
*/

static char		*format_env_variable(char *variable, char *value)
{
	char	*format_env;
	int		len_var;
	int		len_val;

	len_var = ft_strlen(variable);
	len_val = ft_strlen(value);
	format_env = MALLOC(sizeof(char) * (len_var + len_val + 2));
	ft_strcpy(format_env, variable);
	format_env[len_var] = '=';
	ft_strcpy(format_env + len_var + 1, value);
	return (format_env);
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
	index = ft_getenv_index(variable);
	if (index >= 0)
	{
		FREE(g_environ[index]);
		g_environ[index] = format_env;
	}
	else
		g_environ = ft_array_extend(g_environ, format_env, false);
}

/*
** ft_unsetenv:
**
** Remove a variable from the environnement
*/

void			ft_unsetenv(char *variable)
{
	int		index;

	index = ft_getenv_index(variable);
	if (index >= 0)
		ft_array_remove(g_environ, g_environ[index], true);
}
