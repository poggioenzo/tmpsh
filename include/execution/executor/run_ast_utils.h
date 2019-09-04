/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   determine_bytes.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: simrossi <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/27 15:04:52 by simrossi     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/27 15:04:55 by simrossi    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef RUN_AST_UTILS_H
# define RUN_AST_UTILS_H

void		setup_branch_pipe(t_acb *branch, t_acb *next_branch);
void		close_subast_pipe(t_acb *branch);
t_bool		check_background(t_acb *branch, t_pylst *list_branch);
t_bool		check_andor(t_pylst *job_branches);

#endif
