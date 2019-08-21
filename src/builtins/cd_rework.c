#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>

#include "libft.h"

char		*shell_dir;


int			next_fileis(char *abspath, char *expected_name)
{
	if (*abspath == '/')
		abspath++;
	while (*abspath && *expected_name && (*abspath == *expected_name))
	{
		abspath++;
		expected_name++;
	}
	if (!*expected_name && (*abspath == '/' || !*abspath))
		return (1);
	return (0);
}

static void		remove_double_slash(char *path)
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
			ft_memmove(slash, slash + nbr_slash, ft_strlen(slash + nbr_slash) + 1);
		path = slash;
	}
}

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

int		len_filename(char *filename)
{
	int		index;

	index = 1;
	while (filename[index] && filename[index] != '/')
		index++;
	return (index);
}

void		remove_dot(char *absolute, char *position)
{
	int		len_dot;
	int		is_root;
	char	*to_del;

	is_root = absolute == position && *absolute == '/';
	len_dot = len_filename(position);
	to_del = position + len_dot;
	ft_strcpy(position, to_del);
	if (is_root && ft_strlen(absolute) == 0)
		ft_strcpy(absolute, "/");
}

void	reset_previous_dir(char *abspath, char **curr_file)
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
		if (!(dot_end = ft_strchr((*curr_file) + 1 , '/')))
		{
			prev_file += is_root;
			prev_file[0] = '\0';
		}
		else
			ft_strcpy(prev_file, dot_end);
		*curr_file = prev_file;
	}
}

char		*canonicalize(char *path)
{	
	char *prev;
	char *curr;
	int	 is_root;

	remove_double_slash(path);
	prev = NULL;
	curr = path;
	while (curr && *curr)
	{
		if (next_fileis(curr, "."))
			remove_dot(path, curr);
		else if (next_fileis(curr, ".."))
			reset_previous_dir(path, &curr);
		else
			curr = ft_strchr(curr + 1, '/');
	}
}

int		main(int argc, char **argv)
{
	struct stat  info;
	char		*cwd;
	char		*file;
	
	if (argc == 2)
	{
		canonicalize(argv[1]);
		ft_printf("canonique : %s\n", argv[1]);
	}
/*
	shell_dir = getcwd(NULL, 0);
	printf("CWD : %s\n", cwd);
	if (argc == 2)
	{
		printf("check : %s\n", argv[1]);
		if (lstat(argv[1], &info) == -1)
			return (1);
		if (S_IFDIR & info.st_mode)
			printf("directory\n");
		if (S_IFREG & info.st_mode)
			printf("regular file\n");
		if (S_IFLNK & info.st_mode)
			printf("symlink\n");
		int fd = open(argv[1], O_RDONLY);
		fchdir(fd);
		cwd = getcwd(NULL, 0);
		printf("CWD : %s\n", cwd);
	}*/
}
