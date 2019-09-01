#include "libft.h"
#include "tmpsh.h"
#include "variables.h"
#include "hash.h"
#include <sys/stat.h>

/*
** is_directory:
**
** Check if the given filename is a directory.
*/

int is_directory(const char *path)
{
	struct stat statbuf;

	if (stat(path, &statbuf) != 0)
		return (0);
	return (S_ISDIR(statbuf.st_mode));
}

/*
** check_rights:
**
** When the shell research exepected executable, check
** if it's possible to run the given file.
** Check permission + file existence.
*/

static char		*check_rights(char *cmd)
{
	char	*err_msg;

	err_msg = NULL;
	if (access(cmd, F_OK) == -1)
		err_msg = NAME_SH" No such file or directory : %s\n";
	else if (is_directory(cmd))
		err_msg = NAME_SH" %s: is a directory\n";
	else if (access(cmd, X_OK) == -1 || access(cmd, R_OK) == -1)
		err_msg = NAME_SH" permission denied: %s\n";
	if (err_msg)
	{
		ft_dprintf(STDERR_FILENO, err_msg, cmd);
		ft_strdel(&cmd);
	}
	return (cmd);
}

/*
** parse_path:
**
** @command: Command name to concat with PATH folders.
**
** Go through each PATH folders and check if the given command exist.
**
** return : - Absolute path of an executable is command is found.
**			- NULL otherwise.
*/

char	*parse_path(char *command)
{
	char	**folders;
	int		index;
	char	*execname;
	t_hash_exec	*cache;


	if (!ft_getenv("PATH"))
		return (NULL);
	folders = ft_strsplit(ft_getenv("PATH"), ":");
	index = 0;
	while (folders[index])
	{
		execname = ft_filejoin(folders + index++, &command, false, false);
		if (access(execname, F_OK) != -1)
		{
			cache = hash_exec_init(execname); //Control duplication
			insert_value(g_hash, command, cache, _ptr);//Use _t_hash_exec
			cache->count++;
			free_str_array(&folders, 0);
			return (check_rights(execname));
		}
		ft_strdel(&execname);
	}
	free_str_array(&folders, 0);
	ft_dprintf(STDERR_FILENO, NAME_SH" command not found: %s\n", command);
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
	return (parse_path(command));
}
