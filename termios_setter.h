#ifndef TERMIOS_SETTER
# define TERMIOS_SETTER

# include <termios.h>

int				manage_termios(int action);

# define SETUP	1
# define RESET	0


#endif
