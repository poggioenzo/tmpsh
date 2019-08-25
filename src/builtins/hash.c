#include "libft.h"
#include "tmpsh.h"

//Need to initialize the hash table
//ht_new_table(&g_hash, 47, 50);
t_ht_table		*g_hash;

t_hash_exec		*hash_exec_init(char *exec_file)
{
	t_hash_exec		*hash_exec;

	hash_exec = ft_memalloc(sizeof(t_hash_exec));
	hash_exec->exec_file = ft_strdup(exec_file);
	hash_exec->count = 0;
	return (hash_exec);
}

int		display_hash(char **argv)
{
	char			*cmd;
	t_hash_exec		*cache;

	if (t_hash->count == 0)
	{
		ft_dprintf(2, "hash: hash table empty\n");
		return (1);
	}
	ft_printf("hits		command\n");
	while (ht_iter(g_hash, &cmd, (void **)&cache))
		ft_printf("%4.4d	%s\n", cache->count, cache->exec_file);
	return (0);
}

int		hash_options(char **argv)
{
	int		argc;

	argc = ft_arraylen(argv);
	if (ft_start_with(*argv, "-"))
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

int		add_new_command(char **argv)
{
	char	*new_path;
	char	*command;
	t_hash_exec		*cache;

	new_path = argv[1];
	command = argv[2];
	cache = hash_exec_init(new_path);
	insert_value(g_hash, command, cache, _ptr); //Need to use _t_hash_exec
	return (0);
}

int		hash(char **argv, char **environ)
{
	t_pylst		*options;
	t_hash_exec	*cache;

	if (hash_options(argv, &options) == 1)
		return (1);
	if (ft_arraylen(argv) == 0)
		return (display_hash(argv));
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
