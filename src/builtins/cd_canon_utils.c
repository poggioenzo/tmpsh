#include "libft.h"

/*
** next_fileis:
**
** @relpath: relative position in a path.
** @expected_name: Filename who is expected to be the next one.
**
** From a given position, check if the current filename
** is corresponding to the expected one.
*/

int			next_fileis(char *relpath, char *expected_name)
{
	if (*relpath == '/')
		relpath++;
	while (*relpath && *expected_name && (*relpath == *expected_name))
	{
		relpath++;
		expected_name++;
	}
	if (!*expected_name && (*relpath == '/' || !*relpath))
		return (1);
	return (0);
}

/*
** remove_double_slash:
**
** @path: path where double slash have to be removed.
**
** Go through an entire path and remove each duplicate / symbol,
** to keep only one separator between each filename.
*/

void		remove_double_slash(char *path)
{
	char	*slash;
	int		nbr_slash;

	while ((slash = ft_strchr(path, '/')))
	{
		slash++;
		nbr_slash = 0;
		while (slash[nbr_slash] && slash[nbr_slash] == '/')
			nbr_slash++;
		if (nbr_slash)
			ft_memmove(slash, slash + nbr_slash, \
					ft_strlen(slash + nbr_slash) + 1);
		path = slash;
	}
}

/*
** retrieve_prev:
**
** @absfile: Entire filename.
** @curr_file: Current position in absfile.
** @prev_file: Pointer to set at the previous file.
**
** From a given position, retrieve the begining of the filename/component,
** which is preceding the curr_file position.
*/

void		retrieve_prev(char *absfile, char *curr_file, char **prev_file)
{
	char	*finder;

	finder = absfile;
	*prev_file = NULL;
	while (finder != curr_file)
	{
		*prev_file = finder;
		finder = ft_strchr(finder + 1, '/');
	}
}

/*
** remove_dot:
**
** When a single dot is found in the filename,
** remove it from the file.
*/

void		remove_dot(char *absolute, char *position)
{
	int		len_dot;
	int		is_root;
	char	*to_del;

	is_root = absolute == position && *absolute == '/';
	len_dot = 1;
	while (position[len_dot] && position[len_dot] != '/')
		len_dot++;
	to_del = position + len_dot;
	ft_strcpy(position, to_del);
	if (is_root && ft_strlen(absolute) == 0)
		ft_strcpy(absolute, "/");
}

/*
** reset_previous_dir:
**
** Whenever a double dot is found, remove the previous directory
** if it's possbile.
** It will be remove when the previous directory is not a dot-dot
** or if we are on root.
*/

void		reset_previous_dir(char *abspath, char **curr_file)
{
	char		*prev_file;
	char		*dot_end;
	int			is_root;

	retrieve_prev(abspath, *curr_file, &prev_file);
	if (abspath == *curr_file && *abspath == '/')
		prev_file = abspath;
	is_root = prev_file == abspath && *abspath == '/';
	if (!prev_file)
		return ;
	if (!next_fileis(prev_file, "..") || is_root)
	{
		if (!(dot_end = ft_strchr((*curr_file) + 1, '/')))
		{
			prev_file += is_root;
			prev_file[0] = '\0';
		}
		else
			ft_strcpy(prev_file, dot_end);
		*curr_file = prev_file;
	}
}
