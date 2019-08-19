#include "libft.h"
#include "tmpsh.h"

static int		error_options(t_pylst *options)
{
	ft_print("type: invalid option: %s\n", options->value);
	return (free_pylst(&options, 1));
}

int		built_type(char **argv, char **environ)
{
	int		index;
	char	*used_elem;
	t_pylst	*options;
	int		status;

	UNUSED(environ);
	options = argparser(options);
	if (len_pylst(options) > 0)
		return (error_options(options));
	index = 0;
	status = 0;
	while (argv[index])
	{
		if ((used_elem = search_value(g_alias, argv[index])))
			ft_printf("%s is aliased to '%s'\n", argv[index], used_elem);
		else if ((search_value(g_builtins, argv[index])))
			ft_printf("%s is a shell builtin\n");
		else if ((used_elem = get_execname(argv[index])))
			ft_printf("%s\n", used_elem);
		else
			ft_printf("type: %s: not found\n", argv[index]) && status = 1;
		index++;
	}
	return (status);
}
