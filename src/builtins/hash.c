#include "libft.h"
#include "tmpsh.h"

t_ht_table		*g_hash;

/*
** hash_exec_init:
**
** Allocate a single t_hash_exec element.
*/

t_hash_exec		*hash_exec_init(char *exec_file)
{
	t_hash_exec		*hash_exec;

	hash_exec = ft_memalloc(sizeof(t_hash_exec));
	hash_exec->exec_file = ft_strdup(exec_file);
	hash_exec->count = 0;
	return (hash_exec);
}

/*
** display_hash:
**
** Print each command cached in g_hash. Show the number of "hits"
** and the associated execfile.
*/

static int		display_hash(void)
{
	char			*cmd;
	t_hash_exec		*cache;

	if (g_hash->count == 0)
	{
		ft_dprintf(2, "hash: hash table empty\n");
		return (1);
	}
	ft_printf("hits    command\n");
	while (ht_iter(g_hash, &cmd, (void **)&cache))
		ft_printf("%4.4d	%s\n", cache->count, cache->exec_file);
	return (0);
}

/*
** hash_options:
**
** Parse argv options and check if arguments are valid.
** Allowed options are -r and -p, and require specific
** set of arguments.
**
** return: - 1 if any error occur.
**		   - 0 if options are correct.
*/

static int		hash_options(char **argv)
{
	int		argc;

	argc = ft_arraylen(argv);
	if (argc > 0 && ft_start_with(*argv, "-"))
	{
		if (!(ft_strequ(argv[0], "-r") || ft_strequ(argv[0], "-p")))
		{
			ft_dprintf(2, "hash: bad option %s\n", *argv);
			return (1);
		}
		if (ft_strequ(argv[0], "-r") && argc != 1)
		{
			ft_dprintf(2, "hash: -r option: no arguments allowed\n");
			return (1);
		}
		if (ft_strequ(argv[0], "-p") && argc != 3)
		{
			ft_dprintf(2, "hash: hash -p <execfile> <command>\n");
			return (1);
		}
	}
	return (0);
}

/*
** add_new_command:
**
** Register in the g_hash table a new command associated to a file.
*/

static int		add_new_command(char **argv)
{
	char			*new_path;
	char			*command;
	t_hash_exec		*cache;

	new_path = argv[1];
	command = argv[2];
	cache = hash_exec_init(new_path);
	insert_value(g_hash, command, cache, _hash_exec);
	return (0);
}

/*
** built_hash:
**
** hash - remember or repot command locations.
**
** Synopsis: hash [cmd ...]
**			 hash -r
**			 hash -p <execfile> <command>
**
** Options:
** -r : Remove all remembered location.
** -p : Use <execfile> when <command> is used.
**
** Hash display or manage hash location of executable for any command.
** Hash count how many times a given command have been executed.
**
** 1) With no arguments, hash will display all remembered location and their
** number of hits.
** 2) If any <cmd> argument is given, reset to 0 the counter of this command.
*/

int				built_hash(char **argv, NOT_USE(char **environ))
{
	t_hash_exec	*cache;

	if (hash_options(argv) == 1)
		return (1);
	if (ft_arraylen(argv) == 0)
		return (display_hash());
	if (ft_strequ(argv[0], "-r"))
		empty_ht(g_hash);
	else if (ft_strequ(argv[0], "-p"))
		return (add_new_command(argv));
	else
	{
		while (*argv)
		{
			if (!(cache = search_value(g_hash, *argv)))
			{
				ft_dprintf(2, "hash: %s not found\n", *argv);
				return (1);
			}
			cache->count = 0;
			argv++;
		}
	}
	return (0);
}
