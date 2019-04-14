#include "shell_setup.h"
#include "t_cursor_utils.h"
#include "line_utils.h"
#include "prompt.h"
#include "t_caps_utils.h"
#include "t_char_insert.h"
#include "display.h"
#include "history.h"
#include "termios_setter.h"
#include "clipboard.h"
#include "signal_handler.h"
#include <signal.h>

/*
** manage_shell_repr:
**
** Storage function to create or free our t_line and cursor structs.
** 3 action availble : GO_FREE, CREATE or GET.
*/

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
		push_end_line(prompt_line);
		static_prompt = *prompt_line;
		static_cursor = *cursor;
		return (MALLOC_SUCCESS);
	}
	else if (action == GO_FREE)
	{
		free_t_line_lst(&static_prompt, 0);
		dealloc_cursor(&static_cursor, 0);
	}
	else if (action == GET)
	{
		if (prompt_line)
			*prompt_line = static_prompt;
		if (cursor)
			*cursor = static_cursor;
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
	insert_string(&shell_lines->chars, prompt_format, TRUE);
	cursor->column += ft_strlen(prompt_format);
	return (MALLOC_SUCCESS);
}

/*
** shell_cleaner:
**
** Memory utils to clean up all different element allocated statically for
** the shell.
*/

void	shell_cleaner(void)
{
	history_store(GO_FREE, NULL);
	manage_shell_repr(GO_FREE, NULL, NULL);
	manage_termios(RESET);
	clipboard_store(GO_FREE, NULL);
	free_capabilities_struct(&g_caps, 0);
}

/*
** shell_exit:
**
** Leave properly the shell, free all allocated content.
** Print a last time the current shell to remove the fake cursor.
*/

void		shell_exit(int status)
{
	t_line	*shell_repr;
	t_cursor	*cursor;

	manage_shell_repr(GET, &shell_repr, &cursor);
	*cursor = (t_cursor){.row = -1, .column = -1};
	display_shell(shell_repr, cursor, FALSE);
	ft_printf("%s\n", g_caps->reset_cursor);
	shell_cleaner();
	exit(status);
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
		manage_shell_repr(GO_FREE, NULL, NULL);
		return (MALLOC_ERROR);
	}
	signal_setup();
	ft_printf(g_caps->hide_cursor);
	display_shell(*shell, *cursor, TRUE);
	return (MALLOC_SUCCESS);
}

