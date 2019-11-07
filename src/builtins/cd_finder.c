/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   determine_bytes.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: simrossi <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/27 15:04:52 by simrossi     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/30 13:36:01 by simrossi    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"
#include "tmpsh.h"
#include "variables.h"
#include "cd_canon.h"

/*
** get_oldpwd:
**
** Return the environnement variable OLDPWD, display an error
** message if it do not exist.
*/

char				*get_oldpwd(char **environ)
{
	char	*oldpwd;

	if (!(oldpwd = ft_getenv_common("OLDPWD", environ)))
		ft_dprintf(2, "cd : OLDPWD not set.\n");
	return (oldpwd ? ft_strdup(oldpwd) : NULL);
}

/*
** allowed_access:
**
** Check if the given file is existing, and if it's having the
** good permission.
**
** return : - 0 if file do not have to good conditions.
**			- 1 if access is allowed.
*/

int					allowed_access(char *filename, int print_error)
{
	if (access(filename, F_OK) == -1)
	{
		if (print_error == true)
			ft_dprintf(2, "cd: No such file or directory: %s\n", filename);
		return (0);
	}
	if (access(filename, X_OK) == -1)
	{
		if (print_error == true)
			ft_dprintf(2, "cd: Permission denied : %s\n", filename);
		return (0);
	}
	return (1);
}

/*
** parse_cdpath:
**
** @pathname: file to search with CDPATH.
** @environ : buitlin environnement variables
**
** Use the environnement variable CDPATH to search if any directory
** exists by the concatenation of a CDPATH folder and pathname.
**
** Make research has expected by POSIX, by testing for each CDPATH folder
** the value <folder>/<pathname> followed by ./<folder>/<pathname>.
*/

static char			*parse_cdpath(char *pathname, char **environ)
{
	char	*cdpath;
	char	**split_folders;
	int		index;
	char	*new_dir;
	char	*tmp;

	if (!(cdpath = ft_getenv_common("CDPATH", environ)))
		return (pathname);
	split_folders = ft_strsplit(cdpath, ":");
	index = 0;
	new_dir = NULL;
	while (split_folders[index])
	{
		new_dir = ft_filejoin(split_folders + index++, &pathname, false, false);
		if (allowed_access(new_dir, false))
			break ;
		tmp = "./";
		new_dir = ft_filejoin(&tmp, &new_dir, false, true);
		if (allowed_access(new_dir, false))
			break ;
		ft_strdel(&new_dir);
	}
	free_str_array(&split_folders, 0);
	return (new_dir ? new_dir : ft_strdup(pathname));
}

/*
** find_newdir:
**
** Process to POSIX step indicate in
** https://pubs.opengroup.org/onlinepubs/9699919799/utilities/cd.html
** to retrieve the path where we have to change directory.
**
** return : - NULL if no file is found.
**			- canonical filename where try chdir.
*/

char				*find_newdir(char *argument, int p_opt, char **environ)
{
	char	*new_dir;

	if (!argument && !(argument = ft_getenv_common("HOME", environ)))
	{
		ft_dprintf(STDERR_FILENO, NAME_SH" : cd: HOME not set\n");
		return (NULL);
	}
	if (*argument == '/')
		new_dir = ft_strdup(argument);
	else if (next_fileis(argument, "..") || next_fileis(argument, "."))
		new_dir = ft_strdup(argument);
	else if (ft_strequ(argument, "-"))
	{
		if (!(new_dir = get_oldpwd(environ)))
			return (NULL);
	}
	else if (!(new_dir = parse_cdpath(argument, environ)))
		new_dir = argument;
	if (*new_dir != '/' && !p_opt)
		new_dir = ft_filejoin(&g_shell_dir, &new_dir, false, true);
	if (!p_opt)
		canonicalize(new_dir);
	return (new_dir);
}
