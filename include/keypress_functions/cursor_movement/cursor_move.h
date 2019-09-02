#ifndef CURSOR_MOVE_H
# define CURSOR_MOVE_H

# include "tmpsh.h"

void		simple_cursor_move(t_line *shell_repr, char *key, t_cursor *cursor);
int			is_key_movement(char *key);

#endif
