#ifndef CHAR_SELECTION_H
# define CHAR_SELECTION_H

# include "tmpsh.h"

t_char		*get_unlocked_char(t_char *char_lst);
void		get_last_lock(t_char *char_lst, t_char **last_lock);
void		get_last_char(t_char *char_lst, t_char **last_char);
void		search_prev_char(t_char *char_lst, t_char **prev_char,\
				t_char *from);

#endif
