#include <stdarg.h>
#include "libft.h"

/*
** store_long_arg:
**
** Add in the pylst a long option, and remove it from argv.
*/

static void		store_long_arg(t_pylst **args, char **argv, int index)
{
	char *str_arg;

	str_arg = argv[index];
	ft_array_remove(argv, argv[index], 0);
	ft_memmove(str_arg, str_arg + 2, ft_strlen(str_arg + 2) + 1);
	push_pylst(args, str_arg, NO_COPY_BUT_FREE, _chare);
}

/*
** store_short_args:
**
** Parse an argument with a format like : "-abcd", and store each
** option independantly inside the list of options.
** Remove the string from argv.
*/

static void		store_short_args(t_pylst **args, char **argv, int index)
{
	char	*new_option;
	char	*arg_str;

	arg_str = argv[index] + 1;
	while (*arg_str)
	{
		new_option = (char *)ft_memalloc(sizeof(char) * 2);
		new_option[0] = *arg_str;
		push_pylst(args, new_option, NO_COPY_BUT_FREE, _chare);
		arg_str++;
	}
	ft_array_remove(argv, argv[index], 1);
}

/*
** remove_duplicate_options:
**
** Before giving back the list of option, remove duplicate symbol.
*/

static void		remove_duplicate_options(t_pylst **option_list)
{
	char	*option;
	t_pylst	*tmp_opt;

	tmp_opt = *option_list;
	while (tmp_opt)
	{;
		option = tmp_opt->value;
		tmp_opt = tmp_opt->next;
		if (str_in_pylst(tmp_opt, option))
			remove_pylst(option_list, option);
	}
}

/*
** argparser:
**
** From an argv array, parse option and store them in a pylst.
** Remove the option from argv.
**
** Each option is a single element of the returned list, splitting
** option like "-abc" in multiple node.
** Difference can be done between short and long option using the length
** of the string. A long option have at least 2 caracter, when short option
** have a single caracter.
** 
** Stop the option whenever a "--" is find.
** Keep also the "-" argument in argv, at least for cd because of cd.
*/

t_pylst		*argparser(char **argv)
{
	t_pylst		*option_list;
	int			index;

	index = 0;
	option_list = NULL;
	while (argv[index] && !ft_strequ(argv[index], "--"))
	{
		if (ft_start_with(argv[index], "--"))
			store_long_arg(&option_list, argv, index--);
		else if (argv[index][0] == '-' && ft_strlen(argv[index]) > 1)
			store_short_args(&option_list, argv, index--);
		index++;
	}
	if (argv[index] && ft_strequ(argv[index], "--"))
		ft_array_remove(argv, argv[index], 1);
	remove_duplicate_options(&option_list);
	return (option_list);
}
