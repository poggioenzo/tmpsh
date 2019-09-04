/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   determine_bytes.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: simrossi <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/27 15:04:52 by simrossi     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/27 15:04:55 by simrossi    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"
#include "tmpsh.h"
#include "file_rights.h"

#include <sys/stat.h>

/*
** is_directory:
**
** Check if the given filename is a directory.
*/

int		is_directory(const char *path)
{
	struct stat statbuf;

	if (stat(path, &statbuf) != 0)
		return (0);
	return (S_ISDIR(statbuf.st_mode));
}

/*
** check_rights:
**
** @filename : file to check.
** @opts: Use [F | R | X | W]
** @free: indicate if filename have to be free
** @print_error: true if an error output is expected.
**
** Verifiy if the given file is existing with the
** given options.
** Check also if the file is a directory, if expected.
*/

char	*check_rights(char *filename, int opts, t_bool free, \
		t_bool avoid_folder)
{
	char	*error;

	error = NULL;
	if ((opts & F) && access(filename, F_OK) == -1)
		error = NAME_SH" No such file or directory : %s\n";
	else if (avoid_folder && is_directory(filename))
		error = NAME_SH" %s is a directory\n";
	else if ((opts & X) && access(filename, X_OK) == -1)
		error = NAME_SH" Permission denied : %s\n";
	else if ((opts & R) && access(filename, R_OK) == -1)
		error = NAME_SH" Permission denied : %s\n";
	else if ((opts & W) && access(filename, W_OK) == -1)
		error = NAME_SH" Permission denied : %s\n";
	if (error)
	{
		ft_dprintf(2, error, filename);
		if (free == true)
			ft_strdel(&filename);
		else
			filename = NULL;
	}
	return (filename);
}
