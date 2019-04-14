#ifndef SHELL_SETUP_H
# define SHELL_SETUP_H

# include "tmpsh.h"

void			shell_preconfig(t_line **shell, t_cursor **cursor);
void			manage_shell_repr(int action, t_line **prompt_line, \
		t_cursor **cursor);
void		shell_exit(int status);
#endif
