#include "word_move.h"
#include "cursor_dependent_selection.h"
#include "libft.h"
#include "char_utils.h"

/*
** set_last_pos:
**
** Set up to the cursor the last avaible position of the shell.
*/

static void			set_last_pos(t_line *shell_repr, t_cursor *cursor)
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

void		next_word(t_line *shell_repr, t_cursor *cursor)
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
		char_line = cursor_line ? get_unlocked_char(cursor_line->chars) : NULL;
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

static void			store_prev_word(t_line *shell_repr, t_cursor *curr_cursor,
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

void		previous_word(t_line *shell_repr, t_cursor *cursor)
{
	t_cursor	word_cursor;
	t_char		*first_unlock;

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
		first_unlock = get_unlocked_char(shell_repr->chars);
		if (first_unlock)
			cursor->column = first_unlock->position;
		else
			cursor->column = char_lst_len(shell_repr->chars);
	}
}
