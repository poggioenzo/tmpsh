#include "tmpsh.h"
#include "libft.h"

int		built_echo(char **args, char **environ)
{
	int		newline;
	int		error;

	UNUSED(environ);
	newline = 1;
	error = false;
	if (ft_array_in(args, "-n"))
	{
		ft_array_remove(args, "-n", 1);
		newline = 0;
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
