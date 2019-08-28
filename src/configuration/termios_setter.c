#include "termios_setter.h"
#include <fcntl.h>

/*
** manage_termios:
**
** Deactivate or activate echo and canonique mode of the termios,
** depending of the given action.
** Available action : SETUP and RESET.
*/
#include "libft.h"
#include "tmpsh.h"

int				manage_termios(enum e_term_action action)
{
	struct termios			term;
	static struct termios	initial_config;
	static struct termios	shell_config;
	int			fd_term;

	fd_term = open("/dev/tty", O_RDONLY);
	if (action == setup_term)
	{
		tcgetattr(fd_term, &term);
		tcgetattr(fd_term, &initial_config);
		term.c_lflag &= ~(ICANON);
		term.c_lflag &= ~(ECHO);
		shell_config = term;
		tcsetattr(fd_term, 0, &shell_config);
	}
	else if (action == restore_term)
		tcsetattr(fd_term, 0, &shell_config);
	else if (action == remove_term)
		tcsetattr(fd_term, 0, &initial_config);
	return (1);
}
