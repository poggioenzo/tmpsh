#include "cursor_move.h"

/*
** move_left:
**
** Check if the cursor can be moved to the left position,
** decrementing the cursor if it's possible.
*/

static void		move_left(t_line *shell_repr, t_cursor *cursor)
{
	t_char	*curr_char;
	t_char	*prev_char;

	shell_repr = get_cursor_line(shell_repr, cursor);
	curr_char = shell_repr->chars;
	get_cursor_char(cursor, &curr_char, &prev_char);
	if (prev_char && prev_char->lock == FALSE)
		cursor->column--;
}

/*
** move_right:
**
** Check if the cursor can be moved to the left position,
** decrementing the cursor if it's possible.
*/

static void		move_right(t_line *shell_repr, t_cursor *cursor)
{
	t_char	*curr_char;
	t_char	*prev_char;

	shell_repr = get_cursor_line(shell_repr, cursor);
	curr_char = shell_repr->chars;
	get_cursor_char(cursor, &curr_char, &prev_char);
	if (curr_char)
		cursor->column++;
}

/*
** simple_cursor_move:
**
** Manage, depending of the pressed key, where the cursor have to be move.
*/

void		simple_cursor_move(t_line *shell_repr, char *key, t_cursor *cursor)
{
	if (key[2] == 68)
	{
		move_left(shell_repr, cursor);
	}
	else
		move_right(shell_repr, cursor);

}
