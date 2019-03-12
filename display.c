#include "display.h"
#include "t_line_utils.h"
#include "t_caps_utils.h"
#include "t_cursor_utils.h"
#include "screen_size.h"
#include "t_char_utils.h"

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
	int		win_lines;
	int		win_cols;
	int		line_len;
	int		line_to_clean;

	screen_size(&win_cols, &win_lines);
	while (shell_lines)
	{
		line_len = char_lst_len(shell_lines->chars);
		if (!shell_lines->next && is_cursor_last_pos(shell_lines, cursor))
			line_len++;
		line_to_clean = line_len / win_cols;
		line_to_clean += line_len % win_cols > 0;
		clean_lines(line_to_clean, shell_lines->next ? FALSE : TRUE);
		shell_lines = shell_lines->next;
	}
}

/*
** display_shell:
**
** Display the representation of the shell using the t_line and t_char
** structure.
*/

void			display_shell(t_line *prompt_lines, t_cursor *cursor)
{
	int			printed_cursor;
	static int	first_display = TRUE;
	int			deleted_line;

	printed_cursor = FALSE;
	deleted_line = 0;
	if (first_display == TRUE)
		first_display = FALSE;
	else
		reset_cursor(prompt_lines, cursor); // to improve
	while (prompt_lines)
	{
		display_chars(prompt_lines->chars, cursor, prompt_lines->position, 
				&printed_cursor);
		prompt_lines = prompt_lines->next;
		if (prompt_lines)
			write(1, "\n", 1);
		else if (printed_cursor == FALSE)
			show_cursor(' ');
	}
}
