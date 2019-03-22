#include "shell_setup.h"
# include "t_cursor_utils.h"
# include "t_line_utils.h"
# include "prompt.h"
# include "t_caps_utils.h"
# include "t_char_insert.h"
# include "display.h"

/*
** manage_shell_repr:
**
** Storage function to create or free our t_line and cursor structs.
** 2 action availble : FREE or CREATE.
*/

int		fd_debug;

int				manage_shell_repr(int action, t_line **prompt_line, \
		t_cursor **cursor)
{
	static t_line	*static_prompt;
	static t_cursor	*static_cursor;

	if (action == CREATE)
	{
		if (alloc_cursor(cursor) == MALLOC_ERROR)
			return (MALLOC_ERROR);
		*prompt_line = NULL;
		if (push_end_line(prompt_line) == MALLOC_ERROR)
			return (dealloc_cursor(cursor, MALLOC_ERROR));
		static_prompt = *prompt_line;
		static_cursor = *cursor;
		return (MALLOC_SUCCESS);
	}
	else if (action == FREE)
	{
		free_t_line_lst(&static_prompt, 0);
		dealloc_cursor(&static_cursor, 0);
	}
	return (0);
}

/*
** insert_prompt_format:
**
** Get the prompt representation and add it in the t_line structure.
*/

static int				insert_prompt_format(t_line *shell_lines, t_cursor *cursor)
{
	char	*prompt_format;

	if ((prompt_format = format_prompt()) == MALLOC_ERROR)
		return (MALLOC_ERROR);
	if (insert_string(&shell_lines->chars, prompt_format, 1) == MALLOC_ERROR)
		return (ft_strdel_out(&prompt_format, MALLOC_ERROR));
	cursor->column += ft_strlen(prompt_format);
	return (MALLOC_SUCCESS);
}

/*
** shell_preconfig:
**
** Prepare the shell to read input. Allocate t_line, t_cursor and
** t_caps struct.
*/

int				shell_preconfig(t_line **shell, t_cursor **cursor)
{
	int		error;

	error = 1;
	if (!(manage_shell_repr(CREATE, shell, cursor)))
		return (MALLOC_ERROR);
	error = insert_prompt_format(*shell, *cursor) == MALLOC_ERROR ? 0 : 1;
	error = alloc_capabilities_struct(&g_caps) == MALLOC_ERROR ? 0 : 1;
	if (error == 0)
	{
		manage_shell_repr(FREE, NULL, NULL);
		return (MALLOC_ERROR);
	}
	ft_printf(g_caps->hide_cursor);
	display_shell(*shell, *cursor, TRUE);
	return (MALLOC_SUCCESS);
}

