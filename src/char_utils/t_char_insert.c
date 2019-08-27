#include "t_char_insert.h"
#include "char_utils.h"
#include "cursor_dependent_selection.h"
#include "line_utils.h"

/*
** cursor_insert:
**
** Insert a new char at the cursor position, incrementing his position.
*/

void	cursor_insert(t_line *shell_repr, char letter, t_cursor *cursor)
{
	t_char		*prev_char;
	t_line		*cursor_line;

	cursor_line = get_cursor_line(shell_repr, cursor);
	get_cursor_char(cursor, cursor_line->chars, &prev_char);
	insert_char(&prev_char, letter, FALSE);
	cursor->column++;
}

/*
** insert_char:
**
** Insert a single char just after the given t_char * element.
** Protection by creating a new node if the given t_char * is NULL.
*/

void	insert_char(t_char **char_lst, char letter, int lock)
{
	t_char	*new_char;

	new_char = NULL;
	if (!*char_lst)
		create_char(char_lst, letter, 0, lock);
	else
	{
		create_char(&new_char, letter, (*char_lst)->position + 1, lock);
		new_char->next = (*char_lst)->next;
		(*char_lst)->next = new_char;
		increment_char_end(new_char);
	}
}

/*
** insert_string:
**
** Insert from a specific t_char node en entire string.
*/

void	insert_string(t_char **char_lst, char *string, int lock)
{
	if (*string && !*char_lst)
		insert_char(char_lst, *string++, lock);
	while (*string)
	{
		insert_char(char_lst, *string++, lock);
		char_lst = &(*char_lst)->next;
	}
}
