#ifndef OPERAND_CHECK_H
# define OPERAND_CHECK_H

# include "tmpsh.h"

int		check_separator(t_operand **operand_list, t_char **curr_char,\
				int *go_line);
int		check_cmdsubst(t_operand **operand_list, t_char *curr_char, \
				int *to_skip);
int		check_db_quote(t_operand **operand_list);
int		check_closing(t_operand **operand_list, t_char *curr_char);
int		syntax_error(char operator);

#endif
