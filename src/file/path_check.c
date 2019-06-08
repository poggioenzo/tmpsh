#include "tmpsh.h"
#include "environ_utils.h"
#include "libft.h"
#include "file_utils.h"

char	*get_exec_file(char *command)
{
	char	**splitted_path;
	char	*path_str;
	int		index;
	char	*absolute_command;

	if (!(path_str = ft_getenv("PATH")))
		return (NULL);
	if (!(splitted_path = ft_strsplit(path_str, ":")))
		exit(-1);
	index = 0;
	while (splitted_path[index])
	{
		absolute_command = concat_file(splitted_path[index], command, 0, 0);
		if (access(absolute_command, F_OK) == 0)
			return (absolute_command);
		index++;
	}
	return (NULL);
}

