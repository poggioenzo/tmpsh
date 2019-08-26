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

char				*get_oldpwd(void)
{
	char	*oldpwd;

	if (!(oldpwd = ft_getenv("OLDPWD")))
		ft_dprintf(2, "cd : OLDPWD not set.\n");
	return (ft_strdup(oldpwd));
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
			ft_printf("cd: No such file or directory: %s\n", filename);
		return (0);
	}
	if (access(filename, X_OK) == -1)
	{
		if (print_error == true)
			ft_printf("cd: Permission denied : %s\n", filename);
		return (0);
	}
	return (1);
}

/*
** parse_cdpath:
**
** @pathname: file to search with CDPATH.
**
** Use the environnement variable CDPATH to search if any directory
** exists by the concatenation of a CDPATH folder and pathname.
**
** Make research has expected by POSIX, by testing for each CDPATH folder
** the value <folder>/<pathname> followed by ./<folder>/<pathname>.
*/

static char			*parse_cdpath(char *pathname)
{
	char	*cdpath;
	char	**split_folders;
	int		index;
	char	*new_dir;
	char	*tmp;

	if (!(cdpath = ft_getenv("CDPATH")))
		return (pathname);
	split_folders = ft_strsplit(cdpath, ":");
	index = 0;
	new_dir = NULL;
	while (split_folders[index])
	{
		new_dir = ft_filejoin(split_folders + index++, &pathname, false, false);
		if (allowed_access(new_dir, false))
			break ;
		ft_strdel(&new_dir);
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

char				*find_newdir(char *argument, int p_opt)
{
	char	*new_dir;

	if (!argument && !(argument = ft_getenv("HOME")))
		return (NULL);
	if (*argument == '/')
		new_dir = ft_strdup(argument);
	else if (next_fileis(argument, "..") || next_fileis(argument, "."))
		new_dir = ft_strdup(argument);
	else if (ft_strequ(argument, "-"))
	{
		if (!(new_dir = get_oldpwd()))
			return (NULL);
	}
	else if (!(new_dir = parse_cdpath(argument)))
		new_dir = argument;
	if (*new_dir != '/' && !p_opt)
		new_dir = ft_filejoin(&g_shell_dir, &new_dir, false, true);
	if (p_opt)
		canonicalize(new_dir);
	return (new_dir);
}
