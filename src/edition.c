#include "edition.h"
#include <fcntl.h>
#include "libft.h"
#include "t_cursor_utils.h"
#include "t_line_utils.h"
#include "t_char_utils.h"
#include "t_caps_utils.h"
#include "t_char_insert.h"
#include "display.h"
#include "termios_setter.h"
#include <termios.h>
#include "cursor_dependent_selection.h"
#include "cursor_move.h"
#include "shell_setup.h"
#include "newline_keypress.h"
#include "history.h"

void		char_analysis(t_line *shell_repr, char *new_char, t_cursor *cursor)
{
	int error;

	error = TRUE;
	if (ft_isprint(*new_char))
		error *= insert_char(shell_repr, *new_char, cursor);
	else if (*new_char == 127)
		delete_char(shell_repr, cursor);
	else if (is_key_movement(new_char)) 
		simple_cursor_move(shell_repr, new_char, cursor);
	else if (*new_char == '\n')
		error *= newline_check(shell_repr, cursor);


}

int				read_loop(void)
{
	int		read_ret;
	char	buff[PROMPT_BUFF + 1];
	t_cursor	*cursor;
	t_line		*shell_lines;

	shell_preconfig(&shell_lines, &cursor);
	while (1)
	{
		ft_bzero(buff, PROMPT_BUFF);
		read_ret = read(STDIN_FILENO, buff, PROMPT_BUFF);
		buff[read_ret] = '\0';
		char_analysis(shell_lines, buff, cursor);
		display_shell(shell_lines, cursor, FALSE);
	}
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

int		main(int argc, char **argv)
{
	t_hist	*history;
	int		status;

	UNUSED(argc);
	UNUSED(argv);
	manage_termios(SETUP);
	//fd_debug = open("shell_debug",  O_RDWR | O_TRUNC | O_CREAT, 0777);
	fd_debug = open("/dev/ttys002",  O_RDWR | O_TRUNC | O_CREAT, 0777);
	ft_dprintf(fd_debug, "there\n");
	status = store_history(&history);
	//show_history(history);
	read_loop();
	return (0);
}