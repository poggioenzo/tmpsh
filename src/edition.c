#include "edition.h"
#include <fcntl.h>
#include "libft.h"
#include "t_cursor_utils.h"
#include "line_utils.h"
#include "char_utils.h"
#include "t_caps_utils.h"
#include "t_char_insert.h"
#include "display.h"
#include "termios_setter.h"
#include "cursor_dependent_selection.h"
#include "cursor_move.h"
#include "shell_setup.h"
#include "newline_keypress.h"
#include "history.h"
#include "char_concatenation.h"
#include "keyboard.h"
#include "clipboard.h"


int		check_eof(t_line *shell_repr)
{
	t_char	*first_unlock;

	first_unlock = get_unlocked_char(shell_repr->chars);
	if (!first_unlock && !shell_repr->next)
		shell_exit(0);
	return (SUCCESS);
}

int		char_analysis(t_line *shell_repr, char *new_char, t_cursor *cursor)
{
	int status;

	status = SUCCESS;
	if (ft_isprint(*new_char))
		status = insert_char(shell_repr, *new_char, cursor);
	else if (*new_char == 127)
		delete_char(shell_repr, cursor);
	else if (is_key_movement(new_char)) 
		simple_cursor_move(shell_repr, new_char, cursor);
	else if (UP_KEY(new_char) || DOWN_KEY(new_char))
		status = history_manager(new_char, shell_repr, cursor);
	else if (*new_char == '\n')
		status = newline_check(shell_repr, cursor);
	else if (CTRL_D(new_char))
		status = check_eof(shell_repr);
	else if (is_clipoard_key(new_char))
		status = clipoard_manager(new_char, shell_repr, cursor);
	ft_strcpy(g_last_char, new_char);
	return (status);
}

int				read_loop(t_line **shell_lines, t_cursor **cursor)
{
	int		read_ret;
	char	buff[PROMPT_BUFF + 1];
	int			status;
	int			index;

	shell_preconfig(shell_lines, cursor);
	status = MALLOC_SUCCESS;
	while (1)
	{
		ft_bzero(buff, PROMPT_BUFF + 1);
		read_ret = read(STDIN_FILENO, buff, PROMPT_BUFF);
		ft_dprintf(fd_debug, "(%d,%d,%d,%d)\n", buff[0], buff[1], buff[2], buff[3] );
		buff[read_ret] = '\0';
		if (ft_isprint(buff[(index = 0)]))
		{
			while (buff[index])
			{
				status = char_analysis(*shell_lines, buff + index++, *cursor);
				if (status == MALLOC_ERROR)
					return (MALLOC_ERROR);
			}
		}
		else
			status = char_analysis(*shell_lines, (char *)buff, *cursor);
		if (status == MALLOC_ERROR || status == not_nested)
			return (status);
		display_shell(*shell_lines, *cursor, FALSE);
	}
	return (0);
}

void	show_history(t_hist *history)
{
	while (history)
	{
		ft_dprintf(fd_debug, "addresses : %p   | prev : %p | len : %d\n", history, history->prev, 
				ft_strlen(history->line));
		ft_dprintf(fd_debug, "line : %s|\n", history->line);
		history = history->next;
	}
}


int		register_command(char *shell_str)
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

int		prompt_loop(void)
{
	int		status;
	t_line		*shell_repr;
	t_cursor	*cursor;
	char		*shell_str;

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
		manage_shell_repr(FREE, NULL, NULL);
		if (status == MALLOC_ERROR)
			return (status);
		//lexer()
		//executor()
	}
}



int		main(int argc, char **argv)
{
	t_hist	*history;
	int		status;

	UNUSED(argv);
	manage_termios(SETUP);
	fd_debug = open("/dev/ttys002",  O_RDWR | O_TRUNC | O_CREAT, 0777);
	status = history_store(CREATE, &history);
	/*rewrite_history(history);*/
	if (argc == 1)
		return (prompt_loop());
	return (status);
}
