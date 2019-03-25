#ifndef CUT_FUNCTIONS_H
# define CUT_FUNCTIONS_H

# include "tmpsh.h"

int		line_cut(t_line	*shell_repr, t_cursor *cursor);
int		cut_next_word(t_line *shell_repr, t_cursor *cursor);
int		cut_prev_word(t_line *shell_repr, t_cursor *cursor);
int		paste_clipboard(t_line *shell_repr, t_cursor *cursor);

#endif
