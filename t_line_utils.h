#ifndef T_LINE_UTILS_H
# define T_LINE_UTILS_H

# include "tmpsh.h"

int		push_end_line(t_line **line_lst);
int		create_t_line(t_line **new_line, t_line *prev, int position);
int		free_t_line_lst(t_line **line_lst, int status);
int		is_cursor_last_pos(t_line *line_lst, t_cursor *cursor);

#endif
