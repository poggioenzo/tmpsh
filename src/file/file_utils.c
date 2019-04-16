#include "libft.h"

char	*concat_file(char *basedir, char *file, int free_base, int free_file)
{
	int		dir_len;
	char	*abs_file;
	char	*slash_tmp;

	dir_len = ft_strlen(basedir);
	if (basedir[dir_len - 1] == '/')
		abs_file = ft_fstrjoin(&basedir, &file, free_base, free_file);
	else
	{
		slash_tmp = "/";
		if (!(abs_file = ft_fstrjoin(&basedir, &slash_tmp, free_base, 0)))
			exit(-1);
		abs_file = ft_fstrjoin(&abs_file, &file, 1, free_file);
	}
	if (!abs_file)
		exit(-1);
	return (abs_file);
}
