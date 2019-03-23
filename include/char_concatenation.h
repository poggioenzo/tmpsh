#ifndef CHAR_CONCATENATION_H
# define CHAR_CONCATENATION_H

/*
** The last line of this file should be "#endif".
** If not update header by project_manager.py (pm) fails.
*/

#include "tmpsh.h"

char		*format_char_lst(t_char *char_lst, t_cursor *cursor, int line);
char			*concat_shell(t_line *prompt_lines, t_cursor *cursor, \
		int *total_lines);
char			*render_shell_content(t_line *prompt_lines);

#endif
