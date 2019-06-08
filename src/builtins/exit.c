#include "libft.h"

void		built_exit(char **args)
{
	int		argc;
	int		value;

	argc = ft_arraylen(args);
	if (argc > 2)
	{
		ft_dprintf(2, "exit: too many arguments\n");
		return ;
	}
	else if (argc == 1)
		value = ft_atoi(args[0]);
	else
		value = 0;
	exit(value);
}
