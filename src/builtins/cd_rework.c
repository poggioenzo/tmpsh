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

int			file_len(char *path)
{
	int		index;

	index = 0;
	while (path[index] && path[index] != '/')
		index++;
	return (index);
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
		printf("FINDER : %s CURR %S PREV %s\n", finder, curr_file, prev_file);
		*prev_file = finder;
		finder = ft_strchr(finder + 1, '/');
	}
	printf("PREV : %s ---------\n", *prev_file);
}

int			iter_filecompo(char *absfile, char **prev, char **curr)
{
	static char		*curr_save = NULL;

	printf("IN iter save %s : prev %s | curr %s \n",
			curr_save, *prev, *curr);
	if (!curr_save)
	{
		curr_save = absfile;
		*curr = curr_save;
		*prev = NULL;
		return (1);
	}
	else if (!*curr_save)
	{
		curr_save = NULL;
		return (0);
	}
	if (curr_save != *curr)
	{
		curr_save = *curr;
		if (!*curr_save)
			return (0);
		printf("pos %s in %s\n", curr_save, absfile);
		retrieve_prev(absfile, curr_save, prev);
		return (1);
	}
	else
		*prev = curr_save;
	curr_save = ft_strchr(curr_save + 1, '/');
	if (curr_save && curr_save[1])
	{
		*curr = curr_save;
		printf("OUT iter save %s : prev %s | curr %s \n",
				curr_save, *prev, *curr);
		return (1);
	}
	printf("OUT prev %s curr %s\n", *prev, *curr);
	curr_save += ft_strlen(curr_save);
	return (1);
}

int		len_filename(char *filename)
{
	int		index;

	index = 1;
	while (filename[index] && filename[index] != '/')
		index++;
	return (index);
}

void		remove_dot(char *relpath)
{
	int		len_dot;
	int		end_len;

	len_dot = len_filename(relpath);
	end_len = ft_strlen(relpath + len_dot) + 1;
	ft_memmove(relpath, relpath + len_dot, end_len);
}

void	reset_previous_dir(char **curr_file, char *prev_file)
{
	char		*dot_end;

	printf("there prev : %s, curr : %s\n", prev_file, *curr_file);
	if (!prev_file)
		return ;
	if (!next_fileis(prev_file, ".."))
	{
		if (!(dot_end = ft_strchr((*curr_file) + 1 , '/')))
		{
			*prev_file = '\0';
			*curr_file = prev_file;
			printf("CUT\n");
		}
		else
		{
			ft_printf("dot |%s|, prev_file |%s|\n", dot_end, prev_file);
			ft_strcpy(prev_file, dot_end);
			ft_printf("prevdel %s\n", prev_file);
			*curr_file = prev_file;

		}
	}
}

char		*canonicalize(char *path)
{	
	char *prev;
	char *curr;

	remove_double_slash(path);
	prev = NULL;
	curr = NULL;
	while (iter_filecompo(path, &prev, &curr))
	{
		printf("FILE : %s, pos %s\n", path, curr);
		if (next_fileis(curr, "."))
		{
			remove_dot(curr);
			curr = prev;
		}
		else if (next_fileis(curr, ".."))
		{
			reset_previous_dir(&curr, prev);
			ft_printf("WHEN REMOVED %s\n", path);
		}
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
