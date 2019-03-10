#include "edition.h"

int				manage_termios(int action)
{
	struct termios			term;
	static struct termios	save_term;

	if (action == SETUP)
	{
		tcgetattr(0, &term);
		tcgetattr(0, &save_term);
		term.c_lflag &= ~(ICANON);
		term.c_lflag &= ~(ECHO);
		tcsetattr(0, 0, &term);
	}
	else if (action == RESET)
		tcsetattr(0, 0, &save_term);
	return (1);
}

#define CREATE	0
#define FREE	1

int				manage_shell_repr(int action, t_line **prompt_line, t_cursor **cursor)
{
	static t_line	*static_prompt;
	static t_cursor	*static_cursor;
	int				status;

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

void			display_shell(t_line *prompt_lines, t_cursor *cursor)
{
	//Reset termcap position
	while (prompt_lines)
	{
		display_chars(prompt_lines->chars, cursor, prompt_lines->position);
		prompt_lines = prompt_lines->next;
	}
}


int				insert_prompt_format(t_line *shell_lines, t_cursor *cursor)
{
	char	*prompt_format;

	if ((prompt_format = format_prompt()) == MALLOC_ERROR)
		return (MALLOC_ERROR);
	if (insert_string(&shell_lines->chars, prompt_format, 1) == MALLOC_ERROR)
		return (ft_strdel_out(&prompt_format, MALLOC_ERROR));
	cursor->column += ft_strlen(prompt_format);
	return (MALLOC_SUCCESS);
}


int				read_loop(void)
{
	int		read_ret;
	char	buff[PROMPT_BUFF];
	t_cursor	*cursor;
	t_line		*shell_lines;

	if (!(manage_shell_repr(CREATE, &shell_lines, &cursor)))
		return (MALLOC_ERROR);
	if (!(insert_prompt_format(shell_lines, cursor)))
		return (MALLOC_ERROR);
	display_shell(shell_lines, cursor);
	while (1)
	{
		ft_bzero(buff, PROMPT_BUFF);
		read_ret = read(STDIN_FILENO, buff, PROMPT_BUFF);
		buff[read_ret] = '\0';
		printf("%d %d %d %d\n", buff[0], buff[1], buff[2],buff[3]);
	}
}


int		main(int argc, char **argv)
{
	manage_termios(SETUP);
	read_loop();
	return (0);
}
