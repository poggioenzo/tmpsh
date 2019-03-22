#ifndef HISTORY_H
# define HISTORY_H

# include "tmpsh.h"

int		store_history(t_hist **history);
int			rewrite_history(t_hist *history);
int		free_history(t_hist **history, int status);
int		push_t_hist(t_hist **history, char *content, int is_tmp);

#endif
