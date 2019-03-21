#include "t_char_insert.h"
#include "t_char_utils.h"
#include "t_cursor_utils.h"
#include "t_line_utils.h"
#include "line_deletion.h"

/*
** appropriate_char_insert:
**
** Check if we have to add the char at the last position of the t_char *
** or in the middle of the list.
*/

static int		appropriate_char_insert(t_cursor *cursor, t_char *cursor_char,\
		t_char *prev_char, char letter)
{
	t_char	*new_char_node;

	if (!cursor_char && cursor->column == prev_char->position + 1)
		return (push_end_char(&prev_char, letter, 0));
	if (create_char(&new_char_node, letter, cursor->column, FALSE) ==
			MALLOC_ERROR)
		return (MALLOC_ERROR);
	new_char_node->next = cursor_char;
	prev_char->next = new_char_node;
	return (MALLOC_SUCCESS);
}

/*
** insert_char:
**
** Insert a single char in the chained list of t_char.
** Insert the char according to the cursor position.
*/

int			insert_char(t_line *shell_repr, char letter, t_cursor *cursor)
{
	t_char		*cursor_char;
	t_char		*prev_char;
	t_line		*cursor_line;

	cursor_line = get_cursor_line(shell_repr, cursor);
	if (!cursor_line->chars)
	{
		if (push_end_char(&cursor_line->chars, letter, FALSE) == MALLOC_ERROR)
			return (MALLOC_ERROR);
	}
	else
	{
		cursor_char = cursor_line->chars;
		get_cursor_char(cursor, &cursor_char, &prev_char);
		if (appropriate_char_insert(cursor, cursor_char, prev_char, letter) == MALLOC_ERROR)
			return (MALLOC_ERROR);
	}
	cursor->column++;
	update_position(cursor_line->chars);
	return (MALLOC_SUCCESS);
}

enum deletion {del_line, deletion_succeed};

int			del_pos_char(t_char **char_lst, t_cursor *cursor)
{
	t_char	*prev_char;
	t_char	*curr_char;

	if (cursor->column == 0)
		return (deletion_succeed);
	curr_char = *char_lst;
	prev_char = NULL;
	while (curr_char && curr_char->position + 1 != cursor->column)
	{
		prev_char = curr_char;
		curr_char = curr_char->next;
	}
	if (curr_char->lock == TRUE)
	{
		/*if (char_lst_len(*char_lst) == curr_char->position + 1)
			return (del_line);*/
		return (del_line);
	}
	else if (!prev_char)
		*char_lst = curr_char->next;
	else
		prev_char->next = curr_char->next;
	update_position(*char_lst);
	free_t_char(&curr_char);
	cursor->column--;
	return (deletion_succeed);
}

int			delete_char(t_line *shell_repr, t_cursor *cursor)
{
	int status;
	t_line	*cursor_line;

	cursor_line = get_cursor_line(shell_repr, cursor);
	status = del_pos_char(&cursor_line->chars, cursor);
	if (status == del_line)
		delete_line(shell_repr, cursor_line->position, cursor);
	return (status);
}

/*
** insert_string:
**
** Insert an entire string in a t_char list, allocating each char node.
** Update char position at the end.
*/
/*
int			insert_string_bis(t_cursor *cursor, t_char **char_lst, 
		char *string, int lock)
{
	return (0);
}
*/

// Will only insert string at the last position
int			insert_string(t_char **char_lst, char *string, int lock) 
{
	t_char		**start_char;

	start_char = char_lst;
	while (*string)
	{
		if (push_end_char(char_lst, *string, lock) == MALLOC_ERROR)
			return (MALLOC_ERROR);
		char_lst = &(*char_lst)->next;
		string++;
	}
	update_position(*start_char);
	
	return (MALLOC_SUCCESS);
}
