#include "libft.h"
#include "tmpsh.h"

/*
** check_rights:
**
** When the shell research exepected executable, check
** if it's possible to run the given file.
** Check permission + file existence.
*/

char	*check_rights(char *cmd)
{
	if (access(cmd, F_OK) == -1)
	{
		ft_dprintf(STDERR_FILENO, "tmpsh: No such file or directory : %s\n", cmd);
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

char	*get_execname(char *command)
{
	char	*exec_folders;
	char	**splitted_folders;
	int		nbr_folders;
	int		index;
	char	*execname;

	if (ft_strchr(command, '/'))
		return (check_rights(ft_strdup(command)));
	exec_folders = ft_getenv("PATH");
	if (exec_folders)
	{
		splitted_folders = ft_strsplit(exec_folders, ":");
		index = 0;
		nbr_folders = ft_arraylen(splitted_folders);
		while (index < nbr_folders)
		{
			execname = ft_filejoin(splitted_folders[index], cmd, false, false);
			if (access(execname, F_OK) != -1)
				return (check_rights(execname));
			ft_strdel(&execname);
			index++;
		}
		free_str_array(&splitted_folders);
	}
	ft_dprintf(STDERR_FILENO, "tmpsh: command not found: %s\n", command);
	return (NULL);
}
