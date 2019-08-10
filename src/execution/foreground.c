#include <unistd.h>
#include <fcntl.h>
#include "tmpsh.h"

/*
** set_foreground:
**
** @pgid: pgid to push in foreground.
*/

void	set_foreground(pid_t pgid)
{
	int		term_fd;

	term_fd = open("/dev/tty", O_RDONLY);
	tcsetpgrp(term_fd, pgid);
	close(term_fd);
}

/*
** restore_tcattr:
**
** Reset the terminal control's config to the initial state
** when the shell was launched, using the global variable g_tcsettings.
*/

void	restore_tcattr(void)
{
	int		term_fd;

	term_fd = open("/dev/tty", O_RDONLY);
	tcsetattr(term_fd, TCSADRAIN, &g_tcsettings);
	close(term_fd);
}

/*
** get_tpgid:
**
** return : - pgid of the foreground process group.
*/

int		get_tpgid(void)
{
	int		term_fd;
	int		tpgid;

	term_fd = open("/dev/tty", O_RDONLY);
	tpgid = tcgetpgrp(term_fd);
	close(term_fd);
	return (tpgid);
}
