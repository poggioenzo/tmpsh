#include "libft.h"
#include "tmpsh.h"

t_ht_table		*g_alias = NULL;

void		alias_init(void)
{
	ht_new_table(&g_alias, 7, 65);
}

static t_bool		error_args(char **argv)
{
	t_pylst		*options;
	char		*error_opt;
	int			is_error;

	options = argparser(argv);
	is_error = len_pylst(options);
	free_pylst(&options, 0);
	if (is_error)
	{
		error_opt = options->value;
		ft_printf("alias: bad option: %s\n", error_opt);
		return (true);
	}
	return (false);
}

static int		show_alias(void)
{
	char	*alias;
	char	*value;

	while (ht_iter(g_alias, &alias, &value))
		ft_printf("%s='%s'\n", alias, value);
	return (0);
}

static int		set_alias(char *argument)
{
	char	*equal;
	char	*alias;
	char	*value;

	equal = ft_strchr(argument, "=");
	*equal = '\0';
	alias = argument;
	value = equal + 1;
	if (ft_strlen(alias) == 0)
	{
		ft_dprintf(2, "tmpsh: alias: no alias name\n");
		return (1);
	}
	value = ft_strdup(value);
	insert_value(g_alias, alias, value, _chare);
	return (0);
}

int		bulit_alias(char **argv, char **environ)
{
	int		argc;
	int		index;
	char	*argument;
	char	*arg_value;

	if (error_args(argv) == true)
		return (1);
	argc = len_pylst(argv);
	if (argc == 0)
		return (show_alias());
	index = 0;
	while (index < argc)
	{
		argument = argv[index];
		if (!ft_strchr(argument, "="))
		{
			arg_value = search_value(g_alias, argument);
			if (arg_value)
				ft_printf("%s='%s'\n", argument, arg_value);
		}
		else
			if (set_alias(argument) == 1)
				return (1);
	}
	return (0);
}


