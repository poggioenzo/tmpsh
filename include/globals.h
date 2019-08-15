#ifndef GLOBALS_H
# define GLOBALS_H

# include <termios.h>

extern char	**g_environ;
extern t_ht_table	*g_variables;

extern t_ht_table	*g_builtins;
extern int	g_last_status;

extern t_grammar	*g_grammar;

struct termios	g_tcsettings;

#endif
