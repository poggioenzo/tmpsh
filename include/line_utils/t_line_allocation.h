#ifndef T_LINE_ALLOCATION_H
# define T_LINE_ALLOCATION_H

# include "tmpsh.h"

int		free_t_line(t_line **line_lst, int status);
int		free_t_line_lst(t_line **line_lst, int status);
int		create_t_line(t_line **new_line, int position);
int		push_end_line(t_line **line_lst);

#endif
