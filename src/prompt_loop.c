#include "prompt_loop.h"
#include "libft.h"
#include "keypress_functions.h"
#include "configuration.h"
#include "display.h"
#include "history.h"
#include "char_concatenation.h"

/*
** is_printable_str:
**
** Check if the given string contain only printable characters.
*/

static int		is_printable_str(char *string)
{
	while (*string)
	{
		if (!ft_isprint(*string++))
			return (0);
	}
	return (1);
}

/*
** char_loop:
**
** When a new buffer will be read, check if the given string is containing
** multiple character (when copying/pasting), or a single char.
*/

static int			char_loop(t_line *shell_repr, t_cursor *cursor, char *buffer)
{
	int		index;
	int		status;

	index = 0;
	if (is_printable_str(buffer))
	{
		while (buffer[index])
		{
			status = char_analysis(shell_repr, buffer + index++, cursor);
			if (status == MALLOC_ERROR)
				return (MALLOC_ERROR);
		}
	}
	else
		status = char_analysis(shell_repr, buffer, cursor);
	return (status);
}


/*
** read_loop:
**
** Listenning on stdin until the prompt content will be an entire
** command and newline is pressed to send it to the lexer/parser/executer.
** Behave according to each pressed key.
*/

static int				read_loop(t_line **shell_lines, t_cursor **cursor)
{
	int		read_ret;
	char	buff[PROMPT_BUFF + 1];
	int			status;

	shell_preconfig(shell_lines, cursor);
	status = MALLOC_SUCCESS;
	while (1)
	{
		ft_bzero(buff, PROMPT_BUFF + 1);
		read_ret = read(STDIN_FILENO, buff, PROMPT_BUFF);
		buff[read_ret] = '\0';
		status = char_loop(*shell_lines, *cursor, buff);
		if (status == MALLOC_ERROR || status == not_nested)
			return (status);
		display_shell(*shell_lines, *cursor, FALSE);
	}
	return (0);
}

/*
** register_command:
**
** Whenever a new command is send, store it to the current history and rewrite
** the history file.
*/

static int		register_command(char *shell_str)
{
	t_hist	*history;
	char	*shell_cpy;
	int		store_history;

	history_store(GET, &history);
	store_history = !history ? TRUE : FALSE;
	shell_cpy = ft_strdup(shell_str);
	if (!shell_cpy)
		return (MALLOC_ERROR);
	else if (!shell_cpy[0])
		return (ft_strdel_out(&shell_cpy, SUCCESS));
	if (push_t_hist(&history, shell_cpy, FALSE) == MALLOC_ERROR)
		return (ft_strdel_out(&shell_cpy, MALLOC_ERROR));
	if (store_history)
		history_store(STORE, &history);
	return (rewrite_history(history));
}

/*
** prompt_loop:
**
** Loop over and over on read_loop, giving each time a new prompt to type command.
** When a command is send, store this new command in the local history.
*/

int		prompt_loop(void)
{
	int		status;
	t_line		*shell_repr;
	t_cursor	*cursor;
	char		*shell_str;
	t_hist		*history;

	manage_termios(SETUP);
	status = history_store(CREATE, &history); // UNPROTECTED
	while (1)
	{
		shell_repr = NULL;
		cursor = NULL;
		status = read_loop(&shell_repr, &cursor);
		if (status == not_nested)
		{
			shell_str = render_shell_content(shell_repr); //unprotected malloc
			register_command(shell_str); //unprotected malloc
			*cursor = (t_cursor){.row = -1, .column = -1};
			display_shell(shell_repr, cursor, FALSE);
			ft_printf("\n");
		}
		manage_shell_repr(GO_FREE, NULL, NULL);
		if (status == MALLOC_ERROR)
			return (status);
		//lexer()
		//executor()
	}
}
