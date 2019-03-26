#include "edition.h"
#include <fcntl.h>
#include "prompt_loop.h"




int		main(int argc, char **argv)
{
	t_hist	*history;
	int		status;

	UNUSED(argv);
	fd_debug = open("/dev/ttys005",  O_RDWR | O_TRUNC | O_CREAT, 0777);
	if (argc == 1)
		return (prompt_loop());
	return (status);
}
