#include "char_analysis.h"
#include "keypress_functions.h"
#include "keyboard.h"
#include "history.h"
#include "libft.h"
#include "t_char_insert.h"

/*
** char_analysis:
**
** Check the given char serie, which can be a basic ASCII char or an escaped
** sequence, end call the function linked to this key.
** Store the last char in the global g_last_char.
*/

int		char_analysis(t_line *shell_repr, char *new_char, t_cursor *cursor)
{
	int status;

	status = SUCCESS;
	if (ft_isprint(*new_char))
		status = insert_char(shell_repr, *new_char, cursor);
	else if (*new_char == 127)
		delete_char(shell_repr, cursor);
	else if (is_key_movement(new_char)) 
		simple_cursor_move(shell_repr, new_char, cursor);
	else if (UP_KEY(new_char) || DOWN_KEY(new_char))
		status = history_manager(new_char, shell_repr, cursor);
	else if (*new_char == '\n')
		status = newline_check(shell_repr, cursor);
	else if (CTRL_D(new_char))
		status = check_eof(shell_repr);
	else if (is_clipoard_key(new_char))
		status = clipoard_manager(new_char, shell_repr, cursor);
	ft_strcpy(g_last_char, new_char);
	return (status);
}
