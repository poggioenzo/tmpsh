#ifndef OPERAND_DELETION_H
# define OPERAND_DELETION_H

# include "tmpsh.h"

void	delete_operand(t_operand **operand_list, t_operand **to_del);
void	delete_last_operand(t_operand **operand_list);
void	delete_operand_from(t_operand **operand_list, t_operand **from_operand);

#endif
