#include "newline_keypress.h"
#include "t_char_insert.h"
#include "t_char_utils.h"
#include "t_line_utils.h"


static int	is_nested(t_line *shell_repr)
{
	UNUSED(shell_repr);
	return (TRUE);
}

int			newline_check(t_line *shell_repr, t_cursor *cursor)
{
	if (is_nested(shell_repr) == TRUE)
	{
		if (push_end_line(&shell_repr) == MALLOC_ERROR)
			return (MALLOC_ERROR);
		shell_repr = get_last_line(shell_repr);
		if (insert_string(&shell_repr->chars, "> ", TRUE) == MALLOC_ERROR)
			return (MALLOC_ERROR);
		cursor->row = shell_repr->position;
		cursor->column = char_lst_len(shell_repr->chars);
		return (SUCCESS);
	}
	else
	{
		return (SUCCESS);
	}
}
