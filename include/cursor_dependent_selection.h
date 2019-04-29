#ifndef CURSOR_DEPENDENT_SELECTION_H
# define CURSOR_DEPENDENT_SELECTION_H

# include "tmpsh.h"

t_line		*get_cursor_line(t_line *shell_lines, t_cursor *cursor);

t_char		*get_cursor_char(t_cursor *cursor, t_char *char_lst,\
		t_char **prev_char);
t_line	*get_prev_cursor_line(t_cursor *cursor, t_line *shell_repr);
void	get_last_word(t_line *shell_repr, t_cursor *cursor, \
		t_cursor *word_cursor, t_char **word_char);
void		get_next_word(t_line *shell_repr, t_cursor *cursor, \
		t_cursor *word_cursor, t_char **word_char);

#endif 
