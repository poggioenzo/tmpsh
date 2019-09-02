#ifndef TERMIOS_SETTER_H
# define TERMIOS_SETTER_H

# include <termios.h>

enum	e_term_action
{
	remove_config = 0,
	save_config,
	shell_config,
};

int				manage_termios(enum e_term_action action);

#endif
