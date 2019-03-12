#ifndef T_CURSOR_UTILS_H
# define T_CURSOR_UTILS_H

# include "libft.h"
# include "tmpsh.h"
# include "t_caps_utils.h"

typedef	struct
{
	short	row;
	short	column;
}		t_cursor;

int		alloc_cursor(t_cursor **cursor);
int		dealloc_cursor(t_cursor **cursor, int status);
void	show_cursor(char letter);
#endif
