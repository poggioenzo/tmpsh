#include "cursor_dependent_selection.h"
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
	ft_dprintf(fd_debug, "in get_cursor_char : curr %p | prev %p\n", *curr_char, *prev_char);
	ft_dprintf(fd_debug, "pos char : %d | cursor : %d\n", (*curr_char)->position, cursor->column);
	while (*curr_char && (*curr_char)->position != cursor->column)
	{
		ft_dprintf(fd_debug, "start : prev : %p | curr %p\n", *prev_char, *curr_char);
		*prev_char = *curr_char;
		*curr_char = (*curr_char)->next;
		ft_dprintf(fd_debug, "prev : %p | curr : %p\n", *prev_char, *curr_char);
	}
}
