#include "libft.h"
#include "tmpsh.h"

/*
** error_options:
**
** Display an error message if there is any option.
*/

static int		error_options(t_pylst *options)
{
	ft_print("type: invalid option: %s\n", options->value);
	return (free_pylst(&options, 1));
}

/*
** built_type:
**
** type - write a description of command type
**
** Synopsis : type name [...]
**
** Display how name will be interpreted by the
** shell.
**
** Methods:
** - name is a builtin.
** - name is an alias.
** - name is cached command, in hash table.
** - name is a command, searched with PATH.
** - name is an executable file.
**
** output : - absolute filename of the command.
**			- description of the method if no file exist.
**			- error message.
*/

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
