#include "line_deletion.h"
#include "t_line_utils.h"
#include "t_char_utils.h"

void static		update_line_position(t_line *shell_repr)
{
	int		index;
	
	index = 0;
	while (shell_repr)
	{
		shell_repr->position = index++;
		shell_repr = shell_repr->next;
	}
}

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
	prev_line->next = cursor_line->next;
	cursor->row--;
	cursor->column = char_lst_len(prev_line->chars);
	free_t_line(&cursor_line, 0);
	update_line_position(shell_repr);
}
