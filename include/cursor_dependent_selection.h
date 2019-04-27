#ifndef CURSOR_DEPENDENT_SELECTION_H
# define CURSOR_DEPENDENT_SELECTION_H

# include "tmpsh.h"
# ifndef NULL
#  define NULL (void *) 0
# endif

t_line		*get_cursor_line(t_line *shell_lines, t_cursor *cursor);

t_char		*get_cursor_char(t_cursor *cursor, t_char *char_lst,\
		t_char **prev_char);

int		is_cursor_last_pos(t_line *line_lst, t_cursor *cursor);

t_char	*get_cursor_char_only(t_char *char_lst, t_cursor *cursor);
#endif 
