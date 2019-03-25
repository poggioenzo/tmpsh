#ifndef T_OPERAND_ALLOCATION_H
# define T_OPERAND_ALLOCATION_H

# include "tmpsh.h"

int		create_operand(t_operand **operand, int type, char open_char);
int		push_operand(t_operand **operand_list, int type, char open_char);
int		free_operand_node(t_operand **operand_node, int status);
int		free_operand_lst(t_operand **operand_list, int status);

#endif
