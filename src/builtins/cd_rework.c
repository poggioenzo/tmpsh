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
	if (!expected_name && (*abspath == '/' || !*abspath))
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

/*
void		reset_previous_dir(char *abspath, char **curr_pos)
{
	char	*prev_file;
	int		need_move;

	prev_file = *curr_pos;
	if (prev_file - abspath == 0)
		return ;
	while ((prev_file - abspath) > 0 && *prev_file != '/')
		prev_file--;
	if (prev_file == *curr_pos)
		return ;
	if (prev_file == abspath && )
}
*/
void		reset_previous_dir(char *abspath, char **curr_pos)
{
	char	*prev_file;
	char	*tmp_ptr;
	int		need_move;

	tmp_ptr = abspath;
	prev_file = abspath;
	need_move = 0;
	while (*tmp_ptr && tmp_ptr != *curr_pos)
	{
		if (*tmp_ptr == '/' && tmp_ptr + 1 != *curr_pos)
			prev_file = tmp_ptr;
		tmp_ptr++;
	}
	if (tmp_ptr == *curr_pos)
		return ;
	if (prev_file + 1 == *curr_pos)
		need_move = 1;
	else if (!next_fileis(prev_file + 1, ".."))
		need_move = 1;
	if (need_move)
	{
		tmp_ptr = (*curr_pos) + 3;
		ft_memmove(prev_file, tmp_ptr, ft_strlen(tmp_ptr) + 1);
	}
}

char		*canonicalize(char *path)
{	
	char	*curr_pos;

	remove_double_slash(path);
	ft_printf("rm slash : %s\n", path);
	curr_pos = path;
	if (*curr_pos == '/')
		curr_pos++;
	while (curr_pos && *curr_pos)
	{
		if (!ft_strncmp(curr_pos, "./", 2) && curr_pos[2] != '\0')
			ft_memmove(curr_pos, curr_pos + 2, ft_strlen(curr_pos + 2) + 1);
		else if (!next_fileis(curr_pos, "..") && curr_pos[3])
			reset_previous_dir(path, &curr_pos);
		curr_pos = ft_strchr(curr_pos, '/');
		if (curr_pos)
			curr_pos++;
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
