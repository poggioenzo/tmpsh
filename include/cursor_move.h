#ifndef CURSOR_MOVE_H
# define CURSOR_MOVE_H

# include "tmpsh.h"
# include "cursor_dependent_selection.h"

# define ESC(key)		key == 27
# define IS_KEYBOARD(key, index) (ESC(key[index]) && key[index + 1] == 91)

# define LEFT_KEY(key) (IS_KEYBOARD(key, 0) && key[2] == 68)
# define RIGHT_KEY(key) (IS_KEYBOARD(key, 0) && key[2] == 67)
# define MOVE_UP(key) (ESC(key[0]) && IS_KEYBOARD(key, 1) && key[3] == 65)
# define MOVE_DOWN(key) (ESC(key[0]) && IS_KEYBOARD(key, 1) && key[3] == 66)
# define PREV_WORD(key) (ESC(key[0]) && IS_KEYBOARD(key, 1) && key[3] == 68)
# define NEXT_WORD(key) (ESC(key[0]) && IS_KEYBOARD(key, 1) && key[3] == 67)

# define HOME(key) (IS_KEYBOARD(key, 0) && key[2] == 72)
# define END(key) (IS_KEYBOARD(key, 0) && key[2] == 70)
# define CTRL_A(key) (key[0] == 1)
# define CTRL_E(key) (key[0] == 5)
# define CTRL_D(key) (key[0] == 4)

# define CTRL_W(key) (key[0] == 23)
# define CTRL_N(key) (key[0] == 14)
# define CTRL_L(key) (key[0] == 12)
# define CTRL_P(key) (key[0] == 16)

# define UP_KEY(key)	(IS_KEYBOARD(key, 0) && key[2] == 65)
# define DOWN_KEY(key)	(IS_KEYBOARD(key, 0) && key[2] == 66)

void		simple_cursor_move(t_line *shell_repr, char *key, t_cursor *cursor);
int			is_key_movement(char *key);


#endif
