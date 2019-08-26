#include "tmpsh.h"
#include "libft.h"

/*
** built_echo:
**
** echo - Write argument to standard output.
**
** Synopsis : echo [string ...]
**
** Options :
** -n : avoid printing a newline.
*/

int		built_echo(char **args, NOT_USE(char **environ))
{
	int		newline;
	int		error;

	newline = true;
	error = false;
	if (ft_strequ(*args, "-n"))
	{
		args++;
		newline = false;
	}
	while (*args)
	{
		error = ft_printf(*args) == -1 ? true : false;
		if (error == false && *(args + 1))
			error = ft_printf(" ") == -1 ? true : false;
		args++;
	}
	if (error == false && newline)
		error = ft_printf("\n") == -1 ? true : false;
	return (error == true ? -1 : 0);
}
