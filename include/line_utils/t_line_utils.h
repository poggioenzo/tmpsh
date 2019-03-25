#ifndef T_LINE_UTILS_H
# define T_LINE_UTILS_H

# include "tmpsh.h"

void		line_proper(t_line *cursor_line);
void		extract_line(t_line *shell_repr, t_line *to_del);
t_line		*get_last_line(t_line *shell_repr);
void		update_line_lst(t_line *shell_repr);
int			line_lst_len(t_line *shell_repr);

#endif
