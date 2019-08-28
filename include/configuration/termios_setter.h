#ifndef TERMIOS_SETTER
# define TERMIOS_SETTER

# include <termios.h>

enum e_term_action
{
	remove_term = 0,
	setup_term,
	restore_term,
};

int				manage_termios(enum e_term_action action);

#endif
