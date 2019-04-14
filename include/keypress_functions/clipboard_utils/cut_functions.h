#ifndef CUT_FUNCTIONS_H
# define CUT_FUNCTIONS_H

# include "tmpsh.h"

void		line_cut(t_line	*shell_repr, t_cursor *cursor);
void		cut_next_word(t_line *shell_repr, t_cursor *cursor);
void		cut_prev_word(t_line *shell_repr, t_cursor *cursor);
void		paste_clipboard(t_line *shell_repr, t_cursor *cursor);

#endif
