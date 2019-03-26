#include "char_utils.h"
#include "shell_setup.h"

/*
** check_eof:
**
** Whenever CTRL-D is pressed, check if the string if the prompt is empty,
** leave the program if it the case.
*/

int		check_eof(t_line *shell_repr)
{
	t_char	*first_unlock;

	first_unlock = get_unlocked_char(shell_repr->chars);
	if (!first_unlock && !shell_repr->next)
		shell_exit(0);
	return (SUCCESS);
}
