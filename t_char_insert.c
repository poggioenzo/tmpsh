#include "t_char_insert.h"
#include "t_char_utils.h"
#include "t_cursor_utils.h"
#include "t_line_utils.h"

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
	if (create_char(&new_char_node, letter, cursor->column, FALSE) ==
			MALLOC_ERROR)
		return (MALLOC_ERROR);
	new_char_node->next = char_lst;
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
		if (appropriate_char_insert(tmp_char, letter, cursor) == MALLOC_ERROR)
			return (MALLOC_ERROR);
	}
	cursor->column++;
	update_position(cursor_line->chars);
	return (MALLOC_SUCCESS);
}

int			del_pos_char(t_char **char_lst, t_cursor *cursor)
{
	t_char	*prev_char;
	t_char	*curr_char;

	if (cursor->column == 0)
		return (SUCCESS);
	ft_dprintf(fd_debug, "entry %d|%d\n", cursor->row, cursor->column);
	curr_char = *char_lst;
	prev_char = NULL;
	while (curr_char && curr_char->position + 1 != cursor->column)
	{
		prev_char = curr_char;
		curr_char = curr_char->next;
	}
	if (curr_char->lock == TRUE)
	{
		ft_dprintf(fd_debug, "here\n");
		return (SUCCESS);
	}
	else if (!prev_char)
		*char_lst = curr_char->next;
	else
		prev_char->next = curr_char->next;
	free_t_char(&curr_char);
	cursor->column--;
	ft_dprintf(fd_debug, "del %d|%d\n", cursor->row, cursor->column);
	return (SUCCESS);
}

int			delete_char(t_line *shell_repr, t_cursor *cursor)
{
	shell_repr = get_cursor_line(shell_repr, cursor);
	return (del_pos_char(&shell_repr->chars, cursor));
}

/*
** insert_string:
**
** Insert an entire string in a t_char list, allocating each char node.
** Update char position at the end.
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
