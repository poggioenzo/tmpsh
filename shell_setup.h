#ifndef SHELL_SETUP_H
# define SHELL_SETUP_H

# include "tmpsh.h"
# include "t_cursor_utils.h"
# include "t_line_utils.h"
# include "prompt.h"
# include "t_caps_utils.h"
# include "t_char_insert.h"
# include "display.h"

int				shell_preconfig(t_line **shell, t_cursor **cursor);

#endif
