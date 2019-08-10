#include "tmpsh.h"
#include "libft.h"
#include "environ_utils.h"
#include "local_variables.h"

void	setup_variables_elements(char **environ)
{
	duplicate_environ(environ);
	setup_var_table();
}

void	update_var(char *variable, char *value, char *type, t_bool only_env)
{
	char	*saved_var;
	char	*new_var;

	saved_var = ft_getenv(variable);
	if (saved_var || only_env == true)
	{
		if (!saved_var)
			saved_var = "";
		value = ft_strequ(type, "CONCATENATION") ? \
				ft_strjoin(saved_var, value): ft_strdup(value);
		if (!value)
			exit(-1);
		ft_setenv(variable, value);
		ft_strdel(value);
	}
	else
	{
		saved_var = ft_getvar(variable);
		if (ft_strequ(type, "CONCATENATION"))
			value = ft_strjoin(saved_var ?: "", value);
		else
			value = ft_strdup(value);
		insert_value(g_variables, variable, value, _chare);
		ft_strdel(&saved_var);
	}
}

char	*retrieve_variable(char *variable)
{
	char	*variable_str;
	char	*tmp_var;

	variable_str = NULL;
	if (ft_strequ(variable, "?"))
		variable_str = ft_itoa(g_last_status);
	else if (ft_strequ(variable, "$"))
		variable_str = ft_itoa(getpid());
	else
	{
		tmp_var = ft_getenv(variable);
		if (!tmp_var)
			tmp_var = ft_getvar(variable);
		variable_str = ft_strdup(tmp_var?: "");
	}
	if (!variable_str)
		exit(-1);
	return (variable_str);
}
