#ifndef TERMIOS_SETTER
# define TERMIOS_SETTER

# include <termios.h>

enum e_term_action
{
	remove_config = 0,
	save_config,
	shell_config,
};

int				manage_termios(enum e_term_action action);

#endif
