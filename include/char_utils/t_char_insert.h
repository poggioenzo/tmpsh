#ifndef T_CHAR_INSERT_H
# define T_CHAR_INSERT_H

# include "tmpsh.h"
# include "cursor_dependent_selection.h"

void		insert_string(t_char **char_lst, char *string, int lock);
void		insert_char(t_line *shell_repr, char letter, t_cursor *cursor);

#endif
