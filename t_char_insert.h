#ifndef T_CHAR_INSERT_H
# define T_CHAR_INSERT_H

# include "tmpsh.h"

int			insert_string(t_char **char_lst, char *string, int lock);
int			insert_char(t_line *shell_repr, char letter, t_cursor *cursor);
int			del_pos_char(t_char **char_lst, t_cursor *cursor);
int			delete_char(t_line *shell_repr, t_cursor *cursor);

#endif
