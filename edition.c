#include "edition.h"
#include <fcntl.h>

/*
** manage_shell_repr:
**
** Storage function to create or free our t_line and cursor structs.
** 2 action availble : FREE or CREATE.
*/

#define CREATE	0
#define FREE	1

int		fd_debug;

int				manage_shell_repr(int action, t_line **prompt_line, \
		t_cursor **cursor)
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

/*
** insert_prompt_format:
**
** Get the prompt representation and add it in the t_line structure.
*/

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
	return (MALLOC_SUCCESS);
}


void		char_analysis(t_line *shell_repr, char *new_char, t_cursor *cursor)
{
	int error;

	error = TRUE;
	if (ft_isprint(*new_char))
		error *= insert_char(shell_repr, *new_char, cursor);
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
		display_shell(shell_lines, cursor);
		ft_bzero(buff, PROMPT_BUFF);
		read_ret = read(STDIN_FILENO, buff, PROMPT_BUFF);
		buff[read_ret] = '\0';
		char_analysis(shell_lines, buff, cursor);
		//printf("%d %d %d %d", buff[0], buff[1], buff[2],buff[3]);
		//sleep(1);
	}
}

int		main(int argc, char **argv)
{
	fd_debug = open("shell_debug", O_CREAT | O_RDWR | O_APPEND);
	manage_termios(SETUP);
	read_loop();
	return (0);
}
