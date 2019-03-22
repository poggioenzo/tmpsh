#include "line_deletion.h"
#include "t_line_utils.h"
#include "t_char_utils.h"

/*
** update_line_position:
**
** Go through each line and update there position, starting from 0.
*/

static void		update_line_position(t_line *shell_repr)
{
	int		index;
	
	index = 0;
	while (shell_repr)
	{
		shell_repr->position = index++;
		shell_repr = shell_repr->next;
	}
}

/*
** join_end_of_line:
**
** Whenever a line is deleted, try to move the char at the end of the
** deleted string to the upper line.
*/

static void	join_end_of_line(t_char *prev_chars, t_char *cursor_chars, \
		t_cursor *cursor)
{
	t_char	*last_cursor_lock;

	last_cursor_lock = NULL;
	while (cursor_chars && cursor_chars->lock == TRUE)
	{
		last_cursor_lock = cursor_chars;
		cursor_chars = cursor_chars->next;
	}
	cursor->column = extend_char(prev_chars, cursor_chars);
	last_cursor_lock->next = NULL;
}

/*
** delete_line:
**
** Perform line deletion whenever whe are try to delete the beginning of
** a t_line.
** Add to the end of the upper string the content of the deleted string.
*/

void		delete_line(t_line *shell_repr, int position, t_cursor *cursor)
{
	t_line	*prev_line;
	t_line	*cursor_line;

	if (position == 0)
		return ;
	prev_line = NULL;
	cursor_line = shell_repr;
	while (cursor_line && cursor_line->position != position)
	{
		prev_line = cursor_line;
		cursor_line = cursor_line->next;
	}
	join_end_of_line(prev_line->chars, cursor_line->chars, cursor);
	prev_line->next = cursor_line->next;
	cursor->row--;
	free_t_line(&cursor_line, 0);
	update_line_position(shell_repr);
}
