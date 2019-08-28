#include "word_move.h"
#include "cursor_dependent_selection.h"
#include "libft.h"
#include "char_utils.h"
#include "line_utils.h"

/*
** next_word:
**
** Find in our shell representation the next word who follow the cursor.
** Set the cursor to last position of the shell if there is no more word.
*/

void		next_word(t_line *shell_repr, t_cursor *cursor)
{
	t_cursor word_cursor;

	get_next_word(shell_repr, cursor, &word_cursor, NULL);
	ft_memcpy(cursor, &word_cursor, sizeof(t_cursor));
}

/*
** previous_word:
**
** Find the word juste before the cursor. Start from the beginning of the
** shell, store each founded word start until the cursor position.
** Store those new position if a previous word exist.
*/

void		previous_word(t_line *shell_repr, t_cursor *cursor)
{
	t_cursor	word_cursor;

	get_last_word(shell_repr, cursor, &word_cursor, NULL);
	ft_memcpy(cursor, &word_cursor, sizeof(t_cursor));
}
