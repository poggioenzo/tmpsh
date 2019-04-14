#include "display.h"
#include "libft.h"
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
** display_shell:
**
** Display the representation of the shell using the t_line and t_char
** structure.
*/

void		display_shell(t_line *prompt_lines, t_cursor *cursor, int first_display)
{
	static int	displayed_lines = 0;
	int			curr_line_size;
	int			shell_len;
	char		*shell_repr;

	shell_repr = concat_shell(prompt_lines, cursor, &curr_line_size);
	shell_len = ft_strlen(shell_repr);
	if (first_display == FALSE)
		clean_lines(displayed_lines, TRUE);
	displayed_lines = curr_line_size;
	write(STDOUT_FILENO, shell_repr, shell_len);
}
