#ifndef T_CURSOR_UTILS_H
# define T_CURSOR_UTILS_H

# include "tmpsh.h"


int		alloc_cursor(t_cursor **cursor);
int		dealloc_cursor(t_cursor **cursor, int status);
void	show_cursor(char letter);
#endif
