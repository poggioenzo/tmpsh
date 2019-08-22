#include <unistd.h>
#include "libft.h"
#include "tmpsh.h"
//Include for environnement variables (ft_getenv)

static void	print_error(char *msg, char *to_add)
{
	char	*err_msg;

	if (!(err_msg = ft_strjoin(msg, to_add)))
		exit(-1);
	ft_dprintf(STDERR_FILENO, err_msg);
	FREE(err_msg);
}

/*
** check_rights:
**
** @executable: Absolute or relative path to check permission.
**
** From a given path, verify if the file exist, or if the file
** is readable + executable.
**
** return : - If the file have permission to be used with execve,
**			return the path.
**			- Return NULL if it can't be used.
*/

// Should it be static function ?
char	*check_rights(char *executable)
{
	if (access(executable, F_OK) == -1)
	{
		print_error("tmpsh: No such file or directory : ", executable);
		FREE(executable);
		return (NULL);
	}
	if (access(executable, X_OK) == -1 || access(executable, R_OK) == -1)
	{
		print_error("tmpsh: permission denied: ", executable);
		FREE(executable);
		return (NULL);
	}
	return (executable);
}

/*
** find_exec:
**
** @cmd: the command to search in PATH folders.
**
** Try to retrieve the absolute path of the given command.
** For example, get "ls" as command will return "/bin/ls"
**
** return : - First existing file by parsing PATH from right to left
**			folder.
**			- NULL if no file is found.
*/

static char	*find_exec(char *cmd)
{
	char	**exec_folders;
	int		nbr_folder;
	int		index;
	char	*path_env;
	char	*tmp_file;

	if (!(path_env = ft_getenv("PATH")))
		return (NULL);
	if (!(exec_folders = ft_strsplit(path_env, ":")))
		exit(-1);
	nbr_folder = ft_arraylen(exec_folders);
	index = 0;
	tmp_file = NULL;
	while (index < nbr_folder && !tmp_file)
	{
		tmp_file = exec_folders[index];
		if (!(tmp_file = ft_filejoin(&tmp_file, &cmd, FALSE, FALSE)))
			exit(-1);
		if (access(tmp_file, F_OK) != -1)
			return (tmp_file);
		ft_strdel(&tmp_file);
		index++;
	}
	free_str_array(&exec_folders, 0);
	return (tmp_file);
}


/*
** get_execname:
**
** @cmd : single STMT.
**
** Check if cmd if already a file, or if it's a simple
** shell command, search in PATH the corresponding executable file.
**
** return: - On error, NULL if no file is existing, or if the user
**			 have no rights on the file.
**		   - On success, the relative or absolute file to execve,
**			 freshly allocated.
*/

char	*get_execname(char *cmd)
{
	char	*exec_file;

	//ft_strip(cmd); Should I strip the cmd ? Don't think so
	if (ft_incharset('/', cmd))
	{
		if (!(cmd = ft_strdup(cmd)))
			exit(-1);
		return (check_rights(cmd));
	}
	if ((exec_file = find_exec(cmd)))
		return (check_rights(exec_file));
	print_error("tmpsh: command not found: ", cmd);
	return (NULL);
}
