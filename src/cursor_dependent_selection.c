#include "cursor_dependent_selection.h"
#include "char_utils.h"
#include "libft.h"

/*
** get_cursor_line:
**
** Get the line where the cursor is present.
*/

t_line		*get_cursor_line(t_line *shell_lines, t_cursor *cursor)
{
	while (shell_lines->position != cursor->row)
		shell_lines = shell_lines->next;
	return (shell_lines);
}


/*
** get_cursor_char:
**
** Get the t_char * element corresponding to the selected cursor.
** Get also the previous element in the same time.
*/

void	get_cursor_char(t_cursor *cursor, t_char **curr_char,\
		t_char **prev_char)
{
	*prev_char = NULL;
	while (*curr_char && (*curr_char)->position != cursor->column)
	{
		*prev_char = *curr_char;
		*curr_char = (*curr_char)->next;
	}
}

/*
** is_cursor_last_pos:
**
** Check if the cursor is in the last position of the shell.
*/

int		is_cursor_last_pos(t_line *line_lst, t_cursor *cursor)
{
	int		row;

	row = 0;
	while (line_lst->position != cursor->row)
	{
		row++;
		line_lst = line_lst->next;
	}
	return (cursor->column == char_lst_len(line_lst->chars) && 
			cursor->row == row);
}

/*
** get_cursor_char_only:
**
** Allow us to find the t_char element where the cursor is positionned.
*/

t_char	*get_cursor_char_only(t_char *char_lst, t_cursor *cursor)
{
	while (char_lst && char_lst->position != cursor->column)
		char_lst = char_lst->next;
	return (char_lst);
}
