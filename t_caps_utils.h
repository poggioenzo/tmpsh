#ifndef T_CAPS_UTILS_H
# define T_CAPS_UTILS_H

# include <term.h>
# include <stdlib.h>
# include "tmpsh.h"

typedef struct	s_caps
{
	char	*clear;
	char	*video;
	char	*reset_video;
	char	*hide_cursor;
	char	*reset_cursor;
	char	*save_pos;
	char	*reset_pos;
	char	*del_line;
	char	*start_line;
	char	*move_up;
	char	*move_down;
}				t_caps;

int			alloc_capabilities_struct(t_caps **capabilities);
t_caps		*g_caps;

#endif
