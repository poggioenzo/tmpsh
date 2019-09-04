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

#include "char_concatenation.h"
#include "libft.h"
#include "char_utils.h"
#include "screen_size.h"
#include "concatenation_utils.h"

/*
** concat_shell:
**
** Concat an entire shell representation into a single string.
** Count also the number of line in the terminal who will be occuped
** by the shell.
*/

char			*concat_shell(t_line *prompt_lines, t_cursor *cursor, \
		int *total_lines)
{
	char	*shell_str;
	char	*new_line;
	int		line_len;
	t_win	window;
	char	*newline_tmp;

	shell_str = ft_strnew(0);
	*total_lines = 0;
	screen_size(&window);
	while (prompt_lines)
	{
		new_line = format_char_lst(prompt_lines->chars, cursor, \
						prompt_lines->position);
		shell_str = ft_fstrjoin(&shell_str, &new_line, 1, 1);
		line_len = char_lst_len(prompt_lines->chars);
		if (cursor->row == prompt_lines->position && cursor->column == line_len)
			line_len++;
		*total_lines += line_len / window.ws_col;
		*total_lines += line_len % window.ws_col > 0;
		prompt_lines = prompt_lines->next;
		newline_tmp = "\n";
		if (prompt_lines)
			shell_str = ft_fstrjoin(&shell_str, &newline_tmp, 1, 0);
	}
	return (shell_str);
}

/*
** render_shell_content:
**
** Concat in the single string all input given by the user, removing the
** unlocked part of the t_char.
*/

char			*render_shell_content(t_line *prompt_lines)
{
	char	*shell_str;
	char	*new_line;
	char	*newline_tmp;

	shell_str = ft_strnew(0);
	while (prompt_lines)
	{
		history_formatter(&prompt_lines, &new_line);
		shell_str = ft_fstrjoin(&shell_str, &new_line, 1, 1);
		prompt_lines = prompt_lines->next;
		newline_tmp = "\n";
		shell_str = ft_fstrjoin(&shell_str, &newline_tmp, 1, 0);
	}
	return (shell_str);
}
