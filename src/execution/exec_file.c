/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   determine_bytes.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: simrossi <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/27 15:04:52 by simrossi     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/06 10:44:17 by simrossi    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"
#include "tmpsh.h"
#include "variables.h"
#include "hash.h"
#include "file_rights.h"

char			*display_search_error(char *command, t_bool verbose)
{
	if (verbose)
		ft_dprintf(STDERR_FILENO, NAME_SH" command not found: %s\n", command);
	return (NULL);
}

static char		*get_path(void)
{
	char	*path_folders;

	if ((path_folders = ft_getenv("PATH")))
		return (path_folders);
	if ((path_folders = ft_getvar("PATH")))
		return (path_folders);
	return (NULL);
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

char			*parse_path(char *command, t_bool verbose)
{
	char		**folders;
	int			index;
	char		*execname;
	t_hash_exec	*cache;

	verbose = verbose ? VERBOSE : 0;
	if (!get_path())
		return (display_search_error(command, verbose));
	folders = ft_strsplit(get_path(), ":");
	index = 0;
	while (folders[index])
	{
		execname = ft_filejoin(folders + index++, &command, false, false);
		if (access(execname, F_OK) != -1)
		{
			cache = hash_exec_init(execname);
			insert_value(g_hash, command, cache, _hash_exec);
			free_str_array(&folders, 1) && cache->count++;
			return (check_rights(execname, X | R | verbose, true, true));
		}
		ft_strdel(&execname);
	}
	display_search_error(command, verbose);
	free_str_array(&folders, 0);
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

char			*get_execname(char *command, t_bool verbose)
{
	t_hash_exec		*cache;

	verbose = verbose ? VERBOSE : 0;
	if (ft_strlen(command) == 0)
		return (NULL);
	if ((cache = search_value(g_hash, command)))
	{
		if (check_rights(cache->exec_file, F | X | R, false, true))
		{
			cache->count++;
			return (ft_strdup(cache->exec_file));
		}
		else
			delete_value(g_hash, command);
	}
	if (search_value(g_builtins, command))
		return (ft_strdup(command));
	else if (ft_strchr(command, '/'))
		return (check_rights(ft_strdup(command), F | X | R | verbose, 1, 1));
	return (parse_path(command, verbose));
}
