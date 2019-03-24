#ifndef T_LINE_UTILS_H
# define T_LINE_UTILS_H

# include "tmpsh.h"

int		push_end_line(t_line **line_lst);
int		create_t_line(t_line **new_line, int position);
int		free_t_line_lst(t_line **line_lst, int status);
int		free_t_line(t_line **line_lst, int status);
int		is_cursor_last_pos(t_line *line_lst, t_cursor *cursor);
int		line_lst_len(t_line *shell_repr);
t_line		*get_last_line(t_line *shell_repr);
void		extract_line(t_line *shell_repr, t_line *to_del);
void		update_line_lst(t_line *shell_repr);
void    line_proper(t_line *cursor_line);
#endif
