#include "display.h"
#include "line_utils.h"
#include "t_caps_utils.h"
#include "t_cursor_utils.h"
#include "screen_size.h"
#include "char_utils.h"
#include "cursor_dependent_selection.h"
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


/*
** display_shell:
**
** Display the representation of the shell using the t_line and t_char
** structure.
*/

int			display_shell(t_line *prompt_lines, t_cursor *cursor, int first_display)
{
	static int	displayed_lines = 0;
	int			curr_line_size;
	int			shell_len;
	char		*shell_repr;

	DEBUG_print_line(prompt_lines, fd_debug);

	if (!(shell_repr = concat_shell(prompt_lines, cursor, &curr_line_size)))
		return (MALLOC_ERROR);
	shell_len = ft_strlen(shell_repr);
	if (first_display == FALSE)
		clean_lines(displayed_lines, TRUE);
	displayed_lines = curr_line_size;
	write(STDOUT_FILENO, shell_repr, shell_len);
	return (SUCCESS);
}
