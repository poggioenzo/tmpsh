#include "edition.h"
#include <fcntl.h>
#include "prompt_loop.h"

//FOR in_path fct
#include "environ_utils.h"
#include "file_utils.h"
#include "libft.h"

int		in_path(char *command)
{
	char	**splitted_path;
	char	*path_str;
	int		index;
	char	*absolute_command;

	if (!(path_str = ft_getenv("PATH")))
		return (FALSE);
	if (!(splitted_path = ft_strsplit(path_str, ":")))
		exit(-1);
	index = 0;
	while (splitted_path[index])
	{
		absolute_command = concat_file(splitted_path[index], command, 0, 0);
		if (access(absolute_command, F_OK) == 0)
			return (TRUE);
		index++;
	}
	return (FALSE);
}


int		main(int argc, char **argv, char **environ)
{
	int		status = 0;

	UNUSED(argv);
	duplicate_environ(environ);
	fd_debug = open("/dev/ttys001",  O_RDWR | O_TRUNC | O_CREAT, 0777);
	if (argc == 1)
		return (prompt_loop());
	else
	{
		if (in_path(argv[1]) == TRUE)
			ft_printf("in path !\n");
		else
			ft_printf("not in path...\n");
	}
	return (status);
}
