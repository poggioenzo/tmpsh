#ifndef CURSOR_MOVE_H
# define CURSOR_MOVE_H

# include "tmpsh.h"
# include "cursor_dependent_selection.h"

# define LEFT_KEY(key) (key[0] == 27 && key[1] == 91 && key[2] == 68)
# define RIGHT_KEY(key) (key[0] == 27 && key[1] == 91 && key[2] == 67)
# define IS_KEYBOARD(key) (key[0] == 27 && key[1] == 91)

void		simple_cursor_move(t_line *shell_repr, char *key, t_cursor *cursor);


#endif
