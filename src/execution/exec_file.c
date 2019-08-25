#include "libft.h"
#include "tmpsh.h"
#include "variables.h"

/*
** check_rights:
**
** When the shell research exepected executable, check
** if it's possible to run the given file.
** Check permission + file existence.
*/

static char		*check_rights(char *cmd)
{
	if (access(cmd, F_OK) == -1)
	{
		ft_dprintf(STDERR_FILENO, \
				"tmpsh: No such file or directory : %s\n", cmd);
		ft_strdel(&cmd);
		return (NULL);
	}
	if (access(cmd, X_OK) == -1 || access(cmd, R_OK) == -1)
	{
		ft_dprintf(STDERR_FILENO, "tmpsh: permission denied: %s\n", cmd);
		ft_strdel(&cmd);
		return (NULL);
	}
	return (cmd);
}

char	*parse_path(char *command)
{
	char	**folders;
	int		index;
	char	*execname;
	t_hash_exec	*cache;


	if (ft_getenv("PATH"))
	{
		folders = ft_strsplit(ft_getenv("PATH"), ":");
		index = 0;
		while (folders[index])
		{
			execname = ft_filejoin(folders + index++, &command, false, false);
			if (access(execname, F_OK) != -1)
			{
				cache = hash_exec_init(execname);
				insert_value(g_hash, command, cache, _ptr);//Use _t_hash_exec
				cache->count++;
				free_str_array(&folders, 0);
				return (check_rights(execname));
			}
			ft_strdel(&execname);
		}
		free_str_array(&folders, 0);
	}
	return (NULL);
}

/*
** get_execname:
**
** From a given STMT, verify if the given file correspond to a file,
** or if it's a command to search in PATH.
** Check if the given command can be run, display the appropriate
** error message otherwise.
*/

char			*get_execname(char *command)
{
	t_hash_exec		*cache;

	if ((cache = search_value(g_hash, command)))
	{
		cache->count++;
		return (ft_strdup(cache->exec_file));
	}
	else if (search_value(g_builtins, command))
		return (ft_strdup(command));
	else if (ft_strchr(command, '/'))
		return (check_rights(ft_strdup(command)));
	else if (!(execname = parse_path(command)))
		ft_dprintf(STDERR_FILENO, "tmpsh: command not found: %s\n", command);
	return (execname);
}
