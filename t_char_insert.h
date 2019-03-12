#ifndef T_CHAR_INSERT_H
# define T_CHAR_INSERT_H

# include "t_char_utils.h"
# include "t_cursor_utils.h"
# include "t_line_utils.h"

int			insert_string(t_char **char_lst, char *string, int lock);
int			insert_char(t_line *shell_repr, char letter, t_cursor *cursor);
static int		appropriate_char_insert(t_char *char_lst, char letter, \
		t_cursor *cursor);

#endif
