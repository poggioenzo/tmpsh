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
	char	*path_env;
	char	**folders;
	int		index;
	char	*execname;

	if (ft_strchr(command, '/'))
		return (check_rights(ft_strdup(command)));
	if ((path_env = ft_getenv("PATH")))
	{
		folders = ft_strsplit(path_env, ":");
		index = 0;
		while (folders[index])
		{
			execname = ft_filejoin(folders + index++, &command, false, false);
			if (access(execname, F_OK) != -1)
			{
				free_str_array(&folders, 0);
				return (check_rights(execname));
			}
			ft_strdel(&execname);
		}
		free_str_array(&folders, 0);
	}
	ft_dprintf(STDERR_FILENO, "tmpsh: command not found: %s\n", command);
	return (NULL);
}
