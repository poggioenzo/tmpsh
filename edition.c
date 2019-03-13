#include "edition.h"
#include <fcntl.h>



void		char_analysis(t_line *shell_repr, char *new_char, t_cursor *cursor)
{
	int error;

	error = TRUE;
	if (ft_isprint(*new_char))
		error *= insert_char(shell_repr, *new_char, cursor);
	else if (*new_char == 127)
		delete_char(shell_repr, cursor);
	else if (LEFT_KEY(new_char) || RIGHT_KEY(new_char))
		simple_cursor_move(shell_repr, new_char, cursor);
		
	ft_dprintf(fd_debug, "\n");
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
		//printf("%d %d %d %d", buff[0], buff[1], buff[2],buff[3]);
		//sleep(1);
		display_shell(shell_lines, cursor, FALSE);
	}
}

int		main(int argc, char **argv)
{
	fd_debug = open("shell_debug",  O_RDWR | O_TRUNC | O_CREAT, 0777);
	manage_termios(SETUP);
	read_loop();
	return (0);
}
