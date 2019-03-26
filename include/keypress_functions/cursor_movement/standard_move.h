#ifndef STANDARD_MOVE_H
# define STANDARD_MOVE_H

# include "tmpsh.h"

void		move_left(t_line *shell_repr, t_cursor *cursor);
void		move_right(t_line *shell_repr, t_cursor *cursor);
void		move_down(t_line *shell_repr, t_cursor *cursor);
void		move_up(t_line *shell_repr, t_cursor *cursor);

#endif
