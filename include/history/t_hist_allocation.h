#ifndef T_HIST_ALLOCATION_H
# define T_HIST_ALLOCATION_H

# include "tmpsh.h"

void	push_t_hist(t_hist **history, char *content, int is_tmp);
int		free_history(t_hist **history, int status);

#endif
