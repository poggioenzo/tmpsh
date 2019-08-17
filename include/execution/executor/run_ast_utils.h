#ifndef RUN_AST_UTILS_H
# define RUN_AST_UTILS_H

void		setup_branch_pipe(t_ast *ast, int index, t_acb *branch);
void		close_subast_pipe(t_acb *branch);
t_bool		check_background(t_pylst *list_branch, int index);
t_bool		check_andor(t_acb *branch);

#endif
