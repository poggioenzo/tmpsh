#include "tmpsh.h"
#include "environ_utils.h"
#include "prompt_loop.h"
#include <fcntl.h>

#include "libft.h"
#include "builtins.h"

int		main(int argc, char **argv, char **environ)
{
	int		status = 0;

	duplicate_environ(environ);
	fd_debug = open("/dev/ttys003",  O_RDWR | O_TRUNC | O_CREAT, 0777);
	if (argc == 1)
		return (prompt_loop());
	return (status);
}
