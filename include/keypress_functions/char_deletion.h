#ifndef CHAR_DELETION_H
# define CHAR_DELETION_H

# include "tmpsh.h"

enum deletion {del_line, deletion_succeed};

int			delete_char(t_line *shell_repr, t_cursor *cursor);

#endif
