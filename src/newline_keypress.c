#include "newline_keypress.h"
#include "t_char_insert.h"
#include "t_char_utils.h"
#include "t_line_utils.h"


static int	is_nested(t_line *shell_repr)
{
	return (TRUE);
}

int			newline_check(t_line *shell_repr, t_cursor *cursor)
{
	if (is_nested(shell_repr) == TRUE)
	{
		//add newline
		ft_dprintf(fd_debug, "there\n");
		if (push_end_line(&shell_repr) == MALLOC_ERROR)
			return (MALLOC_ERROR);
		shell_repr = get_last_line(shell_repr);
		DEBUG_print_line(shell_repr, fd_debug);
		if (insert_string(&shell_repr->chars, "> ", TRUE) == MALLOC_ERROR)
			return (MALLOC_ERROR);
		DEBUG_print_line(shell_repr, fd_debug);
		DEBUG_print_char(shell_repr->chars, fd_debug);
		ft_dprintf(fd_debug, "mi\n");
		cursor->row = shell_repr->position;
		cursor->column = char_lst_len(shell_repr->chars);
		ft_dprintf(fd_debug, "ma\n");
		return (SUCCESS);
	}
	else
	{
		return (SUCCESS);
	}
}
