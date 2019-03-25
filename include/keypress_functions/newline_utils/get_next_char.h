#ifndef GET_NEXT_CHAR_H
# define GET_NEXT_CHAR_H

#include "tmpsh.h"

int	is_next_char(t_char *curr_char, char letter);
int	charset_in_next_char(t_char *curr_char, char *charset);
int		get_next_char(t_line **shell_repr, t_char **curr_char);

#endif
