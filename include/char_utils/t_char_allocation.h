#ifndef T_CHAR_ALLOCATION_H
# define T_CHAR_ALLOCATION_H

# include "tmpsh.h"


void		push_end_char(t_char **char_node, char letter, int lock);
void	free_t_char(t_char **char_node);
int		free_t_char_lst(t_char **char_lst, int status);
void	create_char(t_char	**char_node, char letter, int position, int lock);

#endif
