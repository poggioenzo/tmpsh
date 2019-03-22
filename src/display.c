#include "display.h"
#include "t_line_utils.h"
#include "t_caps_utils.h"
#include "t_cursor_utils.h"
#include "screen_size.h"
#include "t_char_utils.h"
#include "char_concatenation.h"

/*
** clean_lines:
**
** Delete the given number of line, moving up the cursor each time.
*/

void			clean_lines(int nb_line, int is_last_line)
{
	ft_printf(g_caps->start_line);
	while (nb_line--)
	{
		ft_printf(g_caps->del_line);
		if (nb_line > 0 || is_last_line == FALSE)
			ft_printf(g_caps->move_up);
	}
}

/*
** reset_cursor:
**
** Reset the cursor to the position where the prompt will be printed.
*/

void			reset_cursor(t_line *shell_lines, t_cursor *cursor)
{
	struct winsize	win;
	int		line_len;
	static int	current_shell_size;
	int		tmp_to_clean;	

	screen_size(&win);
	while (shell_lines)
	{
		line_len = char_lst_len(shell_lines->chars);
		if (!shell_lines->next && is_cursor_last_pos(shell_lines, cursor))
			line_len++;
		tmp_to_clean = line_len / win.ws_col;
		tmp_to_clean += line_len % win.ws_col > 1;
		shell_lines = shell_lines->next;
	}
	if (tmp_to_clean > current_shell_size)
		current_shell_size = tmp_to_clean;
	clean_lines(tmp_to_clean, TRUE);
}


char			*concat_shell(t_line *prompt_lines, t_cursor *cursor, \
		int *total_lines)
{
	char	*shell_str;
	char	*new_line;
	int		line_len;
	t_win	window;
	char	*newline_tmp;

	if (!(shell_str = ft_strnew(0)))
		return (NULL);
	*total_lines = 0;
	screen_size(&window);
	while (prompt_lines)
	{
		if (!(new_line = format_char_lst(prompt_lines->chars, cursor, \
						prompt_lines->position)))
			return (NULL);
		if (!(shell_str = ft_fstrjoin(&shell_str, &new_line, 1, 1)))
			return (NULL);
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

int			display_shell(t_line *prompt_lines, t_cursor *cursor, int first_display)
{
	static int	displayed_lines = 0;
	int			curr_size;
	char		*shell_repr;

	if (!(shell_repr = concat_shell(prompt_lines, cursor, &curr_size)))
		return (MALLOC_ERROR);
	if (first_display == FALSE)
		clean_lines(displayed_lines, TRUE);
	displayed_lines = curr_size;
	write(STDOUT_FILENO, shell_repr, ft_strlen(shell_repr));
	return (SUCCESS);
}

/*
** display_shell:
**
** Display the representation of the shell using the t_line and t_char
** structure.
*/

void			display_shell2(t_line *prompt_lines, t_cursor *cursor, int first_display)
{
	int			printed_cursor;

	printed_cursor = FALSE;
	if (first_display == FALSE)
		reset_cursor(prompt_lines, cursor); // to improve
	while (prompt_lines)
	{
		display_chars(prompt_lines->chars, cursor, prompt_lines->position, 
				&printed_cursor);
		if (printed_cursor == FALSE && cursor->row == prompt_lines->position)
			show_cursor(' ');
		else if (prompt_lines)
			write(1, "\n", 1);
		prompt_lines = prompt_lines->next;
	}
}
