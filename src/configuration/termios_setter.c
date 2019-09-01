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
	static struct termios	initial_termios;
	static struct termios	shell_termios;
	int						fd_term;

	fd_term = open("/dev/tty", O_RDONLY);
	if (action == save_config)
	{
		tcgetattr(fd_term, &initial_termios);
		tcgetattr(fd_term, &shell_termios);
		shell_termios.c_lflag &= ~(ICANON);
		shell_termios.c_lflag &= ~(ECHO);
	}
	else if (action == shell_config)
		tcsetattr(fd_term, 0, &shell_termios);
	else if (action == remove_config)
		tcsetattr(fd_term, 0, &initial_termios);
	close(fd_term);
	return (1);
}
