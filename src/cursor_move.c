#include "cursor_move.h"
#include "t_char_utils.h"
#include "libft.h"

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
** cursor_calibration:
**
** Whenever the cursor is moved up or down, set his column position
** depending of the t_char list configuration.
*/

static void		cursor_calibration(t_char *char_lst, t_cursor *cursor)
{
	int		line_len;
	int		lock_len;

	lock_len = char_lock_len(char_lst);
	line_len = char_lst_len(char_lst);
	if (cursor->column > line_len)
		cursor->column = line_len;
	else if (lock_len > cursor->column)
		cursor->column = lock_len;
}

/*
** move_down:
**
** Move down the cursor if it is allowed.
** Recalculate the cursor->column position if needed.
*/

static void		move_down(t_line *shell_repr, t_cursor *cursor)
{
	t_line	*cursor_line;

	cursor_line = get_cursor_line(shell_repr, cursor);
	if (!cursor_line->next)

		return ;
	cursor->row++;
	cursor_line = cursor_line->next;
	cursor_calibration(cursor_line->chars, cursor);
}

/*
** move_up:
**
** Move up the cursor if it is allowed.
** Recalculate the cursor->column position if needed.
*/

static void		move_up(t_line *shell_repr, t_cursor *cursor)
{
	t_line		*cursor_line;

	if (cursor->row == 0)
		return ;
	cursor->row--;
	cursor_line = get_cursor_line(shell_repr, cursor);
	cursor_calibration(cursor_line->chars, cursor);
	return ;
}

/*
** start_line:
**
** Set the cursor to the beginning of his current line
*/

static void		start_line(t_line *shell_repr, t_cursor *cursor)
{
	shell_repr = get_cursor_line(shell_repr, cursor);
	cursor->column = char_lock_len(shell_repr->chars);
}

/*
** end_line:
**
** Set the cursor to the beginning of his current line
*/

static void		end_line(t_line *shell_repr, t_cursor *cursor)
{
	shell_repr = get_cursor_line(shell_repr, cursor);
	cursor->column = char_lst_len(shell_repr->chars);
}

/*
** get_cursor_char_only:
**
** Allow us to find the t_char element where the cursor is positionned.
*/

static t_char	*get_cursor_char_only(t_char *char_lst, t_cursor *cursor)
{
	while (char_lst && char_lst->position != cursor->column)
		char_lst = char_lst->next;
	return (char_lst);
}

/*
** set_last_pos:
**
** Set up to the cursor the last avaible position of the shell.
*/

void			set_last_pos(t_line *shell_repr, t_cursor *cursor)
{
	t_char	*char_lst;

	while (shell_repr->next)
		shell_repr = shell_repr->next;
	char_lst = shell_repr->chars;
	while (char_lst->next)
		char_lst = char_lst->next;
	cursor->row = shell_repr->position;
	cursor->column = char_lst->position + 1;
}

/*
** next_word:
**
** Find in our shell representation the next word who follow the cursor.
** Set the cursor to last position of the shell if there is no more word.
*/

static void		next_word(t_line *shell_repr, t_cursor *cursor)
{
	t_char		*char_line;
	t_line		*cursor_line;

	cursor_line = get_cursor_line(shell_repr, cursor);
	char_line = get_cursor_char_only(cursor_line->chars, cursor);
	while (char_line && ft_isalnum(char_line->letter))
		char_line = char_line->next;
	while (cursor_line)
	{
		while (char_line && ft_isalnum(char_line->letter) == FALSE)
			char_line = char_line->next;
		if (char_line)
			break ;
		cursor_line = cursor_line->next;
		char_line = cursor_line ? cursor_line->chars : NULL;
	}
	if (cursor_line)
	{
		cursor->column = char_line->position;
		cursor->row = cursor_line->position;
	}
	else
		set_last_pos(shell_repr, cursor);
}

/*
** get_unlocked_char:
**
** Get the first char in t_char list whom is unlocked.
*/

static t_char	*get_unlocked_char(t_char *char_lst)
{
	while (char_lst && char_lst->lock == TRUE)
		char_lst = char_lst->next;
	return (char_lst);
}

/*
** is_cursor_pos:
**
** Condition to check according to a t_line and a t_char if we are on
** the cursor position.
*/

static int		is_cursor_pos(t_line *shell_repr, t_char *char_lst, \
		t_cursor *cursor)
{
	return (shell_repr->position == cursor->row && \
			char_lst->position == cursor->column);
}

/*
** store_prev_word:
**
** Parse the shell representation from the beginning, store the position
** of each word start until we arrive to the cursor position.
*/

void			store_prev_word(t_line *shell_repr, t_cursor *curr_cursor,
		t_cursor *prev_cursor)
{
	t_char		*char_line;
	int			in_word;

	in_word = FALSE;
	while (shell_repr && shell_repr->position <= curr_cursor->row)
	{
		char_line = get_unlocked_char(shell_repr->chars);
		while (char_line && !is_cursor_pos(shell_repr, char_line, curr_cursor))
		{
			if (ft_isalnum(char_line->letter) && in_word == FALSE)
			{
				in_word = TRUE;
				prev_cursor->row = shell_repr->position;
				prev_cursor->column = char_line->position;
			}
			else if (ft_isspace(char_line->letter) && in_word == TRUE)
				in_word = FALSE;
			char_line = char_line->next;
		}
		in_word = FALSE;
		shell_repr = shell_repr->next;
	}
}

/*
** previous_word:
**
** Find the word juste before the cursor. Start from the beginning of the
** shell, store each founded word start until the cursor position.
** Store those new position if a previous word exist.
*/

static void		previous_word(t_line *shell_repr, t_cursor *cursor)
{
	t_cursor	word_cursor;

	word_cursor = (t_cursor){.row = -1, .column = -1};
	store_prev_word(shell_repr, cursor, &word_cursor);
	if (word_cursor.row != -1)
	{
		cursor->row = word_cursor.row;
		cursor->column = word_cursor.column;
	}
	else
	{
		cursor->row = 0;
		cursor->column = get_unlocked_char(shell_repr->chars)->position;
	}
}

/*
** is_key_movement:
**
** Check if the given key corresponding to a cursor control touch
*/

int			is_key_movement(char *key)
{
	return (LEFT_KEY(key) || RIGHT_KEY(key) || MOVE_UP(key) \
			|| MOVE_DOWN(key) || HOME(key) || END(key) || CTRL_A(key) ||
			CTRL_E(key) || PREV_WORD(key) || NEXT_WORD(key));
}

/*
** simple_cursor_move:
**
** Manage, depending of the pressed key, where the cursor have to be move.
*/

void		simple_cursor_move(t_line *shell_repr, char *key, t_cursor *cursor)
{
	if (LEFT_KEY(key))
		move_left(shell_repr, cursor);
	else if (RIGHT_KEY(key))
		move_right(shell_repr, cursor);
	else if (MOVE_UP(key))
		move_up(shell_repr, cursor);
	else if (MOVE_DOWN(key))
		move_down(shell_repr, cursor);
	else if (HOME(key) || CTRL_A(key))
		start_line(shell_repr, cursor);
	else if (END(key) || CTRL_E(key))
		end_line(shell_repr, cursor);
	else if (PREV_WORD(key))
		previous_word(shell_repr, cursor);
	else if (NEXT_WORD(key))
		next_word(shell_repr, cursor);
}
