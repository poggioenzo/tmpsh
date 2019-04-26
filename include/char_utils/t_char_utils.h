#ifndef T_CHAR_UTILS_H
# define T_CHAR_UTILS_H

# include "tmpsh.h"

int			extend_char(t_char *old_chars, t_char *char_to_add);
void		update_position(t_char *char_lst);
int			char_lst_len(t_char *char_lst);
int			char_lock_len(t_char *char_lst);
void	increment_char_end(t_char *char_lst);
#endif
