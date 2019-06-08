
#include "libft.h"

void	built_echo(char **args)
{
	int		newline;

	newline = 1;
	if (ft_array_in(args, "-n"))
	{
		ft_array_remove(args, "-n", 1);
		newline = 0;
	}
	while (*args)
	{
		ft_printf(*args);
		if (*(args + 1))
			ft_printf(" ");
		args++;
	}
	if (newline)
		ft_printf("\n");
}
