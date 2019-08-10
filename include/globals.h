#ifndef GLOBALS_H
# define GLOBALS_H

# include <termios.h>

/*
** Useful structs prototype from libft
*/
typedef struct s_pylst	t_pylst;
typedef struct s_ht_table	t_ht_table;
typedef signed int			pid_t;

extern char	**g_environ;
extern t_ht_table	g_variables;

extern int	g_last_status;

struct termios	g_tcsettings;

#endif
