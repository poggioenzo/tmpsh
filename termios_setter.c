#include "termios_setter.h"

/*
** manage_termios:
**
** Deactivate or activate echo and canonique mode of the termios,
** depending of the given action.
** Available action : SETUP and RESET.
*/

int				manage_termios(int action)
{
	struct termios			term;
	static struct termios	save_term;

	if (action == SETUP)
	{
		tcgetattr(0, &term);
		tcgetattr(0, &save_term);
		term.c_lflag &= ~(ICANON);
		term.c_lflag &= ~(ECHO);
		tcsetattr(0, 0, &term);
	}
	else if (action == RESET)
		tcsetattr(0, 0, &save_term);
	return (1);
}
