/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_readdir.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: simrossi <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/05 13:14:05 by simrossi     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/07 17:27:09 by simrossi    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>
#include <stdio.h>
#include <dirent.h>
#include "libft.h"

static int		is_link(char **filename)
{
	struct stat	info;
	char		buff[PATH_MAX];
	char		*directory;
	char		*buff_ptr;

	if (lstat(*filename, &info) == -1)
		return (-1);
	if (S_ISLNK(info.st_mode))
	{
		if (readlink(*filename, buff, PATH_MAX) == -1)
			return (-1);
		if (!(directory = dirname(*filename)))
			return (-1);
		buff_ptr = buff;
		if (!(*filename = ft_filejoin(&buff_ptr, &directory, 0, 1)))
			return (-1);
	}
	return (S_ISLNK(info.st_mode));
}

static int		delete_subfile(t_subfile **file_lst, int status)
{
	t_subfile	*tmp_file;
	t_subfile	*next_file;

	tmp_file = *file_lst;
	while (tmp_file)
	{
		next_file = tmp_file->next;
		ft_strdel(&tmp_file->filename);
		free(tmp_file);
		tmp_file = next_file;
	}
	*file_lst = NULL;
	return (status);
}

static int		push_subfile(t_subfile **file_lst, struct dirent *inode)
{
	if (!*file_lst)
	{
		if (!(*file_lst = (t_subfile *)malloc(sizeof(t_subfile) * 500)))
			return (-1);
		(*file_lst)->next = NULL;
		if (!((*file_lst)->filename = ft_strdup(inode->d_name)))
			return (delete_subfile(file_lst, -1));
	}
	else
	{
		while ((*file_lst)->next)
			file_lst = &(*file_lst)->next;
		return (push_subfile(&(*file_lst)->next, inode));
	}
	return (1);
}

static int		read_files(char *directory, int *len, t_subfile **ptr_lst)
{
	DIR				*open_dir;
	struct dirent	*sub_file;
	t_subfile		*file_lst;

	file_lst = NULL;
	if (!(open_dir = opendir(directory)))
		return (-1);
	while ((sub_file = readdir(open_dir)))
		if (push_subfile(&file_lst, sub_file) == -1)
			return (delete_subfile(&file_lst, -1));
	closedir(open_dir);
	*ptr_lst = file_lst;
	*len = 0;
	while (file_lst)
	{
		file_lst = file_lst->next;
		(*len)++;
	}
	return (1);
}

/*
** ft_readdir:
**
** Parse a directory and stock each filename in a char ** variable.
**
** return value:
** - 0 if an error occur, 1 otherwise.
*/

int				ft_readdir(char *directory, char ***files_strings)
{
	int			link;
	int			lst_len;
	t_subfile	*file_lst;
	t_subfile	*tmp_lst;

	if ((link = is_link(&directory)) == -1)
		return (0);
	lst_len = 0;
	if (read_files(directory, &lst_len, &file_lst) == -1)
		return (0);
	if (!(*files_strings = (char **)malloc(sizeof(char *) * (lst_len + 1))))
		return (delete_subfile(&file_lst, 0));
	lst_len = 0;
	tmp_lst = file_lst;
	while (file_lst)
	{
		if (!(files_strings[0][lst_len++] = ft_strdup(file_lst->filename)))
		{
			free_str_array(files_strings, -1);
			return (delete_subfile(&tmp_lst, 0));
		}
		file_lst = file_lst->next;
	}
	files_strings[0][lst_len] = NULL;
	return (delete_subfile(&tmp_lst, 1));
}
