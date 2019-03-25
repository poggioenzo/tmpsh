#ifndef CHAR_SKIP_H
# define CHAR_SKIP_H

# include "tmpsh.h"

int		skip_quote(t_line **shell_repr, t_char **curr_char, \
				t_operand **operand_list);
void	escape_char(t_char *curr_char, t_line *shell_repr, int *go_line, \
		int *char_to_skip);
void		skip_char(t_line **shell_repr, t_char **curr_char, int *to_skip);

#endif
