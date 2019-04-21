#include "tmpsh.h"
#include "environ_utils.h"
#include "prompt_loop.h"
#include <fcntl.h>

int		main(int argc, char **argv, char **environ)
{
	int		status = 0;

	UNUSED(argv);
	duplicate_environ(environ);
	fd_debug = open("/dev/ttys001",  O_RDWR | O_TRUNC | O_CREAT, 0777);
	if (argc == 1)
		return (prompt_loop());
	return (status);
}
