#include "t_char_insert.h"

/*
** appropriate_char_insert:
**
** Check if we have to add the char at the last position of the t_char *
** or in the middle of the list.
*/

static int		appropriate_char_insert(t_char *char_lst, char letter, \
		t_cursor *cursor)
{
	t_char	*new_char_node;

	if (!char_lst->next && cursor->column == char_lst->position + 1)
		return (push_end_char(&char_lst, letter, 0));
	if (create_char(&new_char_node, letter, cursor->column, char_lst->prev) ==
			MALLOC_ERROR)
		return (MALLOC_ERROR);
	new_char_node->next = char_lst;
	char_lst->prev = new_char_node;
}

/*
** insert_char:
**
** Insert a single char in the chained list of t_char.
** Insert the char according to the cursor position.
*/

int			insert_char(t_line *shell_repr, char letter, t_cursor *cursor)
{
	t_char		*tmp_char;
	t_line		*cursor_line;

	cursor_line = get_cursor_line(shell_repr, cursor);
	if (!cursor_line->chars)
	{
		if (push_end_char(&cursor_line->chars, letter, FALSE) == MALLOC_ERROR)
			return (MALLOC_ERROR);
	}
	else
	{
		tmp_char = cursor_line->chars;
		while (tmp_char->next && tmp_char->position != cursor->column)
			tmp_char = tmp_char->next;
		if (appropriate_char_insert(tmp_char, cursor, letter) == MALLOC_ERROR)
			return (MALLOC_ERROR);
	}
	cursor->column++;
	update_position(*char_lst);
	return (MALLOC_SUCCESS);
}

/*
** insert_string:
**
** Insert an entire string in a t_char list, allocating each char node.
** Update char position at the end.
*/

int			insert_string(t_char **char_lst, char *string, int lock)
{
	t_char		*tmp_char;

	tmp_char = *char_lst;
	while (*string)
	{
		if (push_end_char(char_lst, *string, lock) == MALLOC_ERROR)
			return (MALLOC_ERROR);
		char_lst = &(*char_lst)->next;
		string++;
	}
	update_position(*char_lst);
	return (MALLOC_SUCCESS);
}
