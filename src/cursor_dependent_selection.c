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

t_char	*get_cursor_char(t_cursor *cursor, t_char *char_lst,\
		t_char **prev_char)
{
	t_char	*cursor_char;

	if (prev_char)
		*prev_char = NULL;
	cursor_char = char_lst;
	while (cursor_char && cursor_char->position != cursor->column)
	{
		if (prev_char)
			*prev_char = cursor_char;
		cursor_char = cursor_char->next;
	}
	return (cursor_char);
}
