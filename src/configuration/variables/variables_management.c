#include "tmpsh.h"
#include "libft.h"
#include "variables.h"
#include "environ_setup.h"

/*
** setup_variables_elements:
**
** Allocate hash table for local variable and duplicate the environ
** variables.
*/

void	setup_variables_elements(char **environ)
{
	duplicate_environ(environ);
	setup_var_table();
}

/*
** update_var:
**
** @variable: Variable to update.
** @value: new value for the variable.
** @type: Operation type, if it's a CONCATENATION or an ASSIGNATION_EQUAL.
** @only_env: If the variable should set only to the local environnement.
**
** Manage the update of a variable. Check if the change have to be done
** for local variables of environnement variables.
** Behave properly if the assignement is a concatenation or not.
*/

void	update_var(char *variable, char *value, char *type, t_bool only_env)
{
	char	*saved_value;

	saved_value = ft_getenv(variable);
	if (saved_value || only_env == true)
	{
		if (!saved_value)
			saved_value = "";
		value = ft_strequ(type, "CONCATENATION") ? \
				ft_strjoin(saved_value, value) : ft_strdup(value);
		ft_setenv(variable, value);
		ft_strdel(&value);
	}
	else
	{
		if (ft_strequ(type, "CONCATENATION"))
		{
			saved_value = ft_getvar(variable);
			value = ft_strjoin(saved_value ? saved_value : "", value);
		}
		else
			value = ft_strdup(value);
		ft_setvar(variable, value);
	}
}

/*
** retrieve_variable:
**
** @variable: Searched variable.
**
** Search in environnement or local variables if the given value is
** available.
**
** return : - Allocated string of the value if the variable exits.
**			- Allocated empty string if the variable isn't available.
*/

char	*retrieve_variable(char *variable)
{
	char	*value;

	if (ft_strequ(variable, "?"))
		return (ft_itoa(g_last_status));
	else if (ft_strequ(variable, "$"))
		return (ft_itoa(getpid()));
	value = ft_getenv(variable);
	if (!value)
		value = ft_getvar(variable);
	return (ft_strdup(value ? value : ""));
}
