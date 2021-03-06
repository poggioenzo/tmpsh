/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   determine_bytes.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: simrossi <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/27 15:04:52 by simrossi     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/27 15:04:55 by simrossi    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "prompt_loop.h"
#include "libft.h"
#include "keypress_functions.h"
#include "configuration.h"
#include "display.h"
#include "history.h"
#include "signal_handler.h"
#include "reset_signals.h"

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

static int		char_loop(t_line **shell_repr, t_cursor **cursor, char *buffer)
{
	int				index;
	int				is_newline;

	index = 0;
	if (is_printable_str(buffer))
	{
		ignore_prompt_signals();
		while (buffer[index])
		{
			is_newline = buffer[index] == '\n';
			if (is_newline)
				signal_setup();
			char_analysis(shell_repr, buffer + index++, cursor);
			if (is_newline)
				ignore_prompt_signals();
		}
		signal_setup();
		return (true);
	}
	return (char_analysis(shell_repr, buffer, cursor));
}

/*
** prompt_loop:
**
** Listenning on stdin until the prompt content will be an entire
** command and newline is pressed to send it to the lexer/parser/executer.
** Behave according to each pressed key.
*/

void			prompt_loop(void)
{
	int			read_ret;
	char		buff[PROMPT_BUFF + 1];
	t_cursor	*cursor;
	t_line		*shell_repr;

	manage_termios(shell_config);
	history_store(CREATE, NULL);
	shell_preconfig(&shell_repr, &cursor);
	while (1)
	{
		ft_bzero(buff, PROMPT_BUFF + 1);
		read_ret = read(STDIN_FILENO, buff, PROMPT_BUFF);
		if (read_ret == -1)
			exit(-1);
		buff[read_ret] = '\0';
		if (char_loop(&shell_repr, &cursor, buff) == true)
			display_shell(shell_repr, cursor, false);
	}
}
