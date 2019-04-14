#include "t_char_insert.h"
#include "char_utils.h"
#include "cursor_dependent_selection.h"
#include "line_utils.h"

/*
** appropriate_char_insert:
**
** Check if we have to add the char at the last position of the t_char *
** or in the middle of the list.
*/

static void		appropriate_char_insert(t_cursor *cursor, t_char *cursor_char,\
		t_char *prev_char, char letter)
{
	t_char	*new_char_node;

	if (!cursor_char && cursor->column == prev_char->position + 1)
		push_end_char(&prev_char, letter, FALSE);
	else
	{
		create_char(&new_char_node, letter, cursor->column, FALSE);
		new_char_node->next = cursor_char;
		prev_char->next = new_char_node;
	}
}

/*
** insert_char:
**
** Insert a single char in the chained list of t_char.
** Insert the char according to the cursor position.
*/

void		insert_char(t_line *shell_repr, char letter, t_cursor *cursor)
{
	t_char		*cursor_char;
	t_char		*prev_char;
	t_line		*cursor_line;

	cursor_line = get_cursor_line(shell_repr, cursor);
	if (!cursor_line->chars)
		push_end_char(&cursor_line->chars, letter, FALSE);
	else
	{
		cursor_char = cursor_line->chars;
		get_cursor_char(cursor, &cursor_char, &prev_char);
		appropriate_char_insert(cursor, cursor_char, prev_char, letter);
	}
	cursor->column++;
	update_position(cursor_line->chars);
}

/*
** insert_string:
**
** Insert a entire string at the end of the t_char lst.
** Optimize the insertion by moving on the current t_char pointer
** after each insertion.
*/

void		insert_string(t_char **char_lst, char *string, int lock) 
{
	t_char		**start_char;

	start_char = char_lst;
	while (*string)
	{
		push_end_char(char_lst, *string, lock);
		char_lst = &(*char_lst)->next;
		string++;
	}
	update_position(*start_char);
}
