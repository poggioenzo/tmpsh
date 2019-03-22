#ifndef T_BRACKET_UTILS_H
# define T_BRACKET_UTILS_H

# include "tmpsh.h"

t_operand	*get_last_bracket(t_operand *operand_list);
int		free_operand_lst(t_operand **operand_list, int status);
int		push_operand(t_operand **operand_list, int type, char bracket);
void	delete_operand(t_operand **operand_list, t_operand **to_del);
void	delete_last_operand(t_operand **operand_list);
void	delete_operand_from(t_operand **operand_list, t_operand **from_operand);
#endif
