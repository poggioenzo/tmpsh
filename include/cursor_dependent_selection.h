#ifndef CURSOR_DEPENDENT_SELECTION_H
# define CURSOR_DEPENDENT_SELECTION_H

# include "tmpsh.h"
# ifndef NULL
#  define NULL (void *) 0
# endif

t_line		*get_cursor_line(t_line *shell_lines, t_cursor *cursor);

void	get_cursor_char(t_cursor *cursor, t_char **curr_char,\
		t_char **prev_char);

#endif 
