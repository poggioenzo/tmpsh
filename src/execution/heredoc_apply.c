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

#include "tmpsh.h"
#include "libft.h"

/*
** heredoc_apply:
**
** @redirections_list: All redirection of a branch.
** @func: Function to apply on each heredoc.
**
** Go through each redirection of a single branch, and apply
** the given function on each available HEREDOC.
*/

void	heredoc_apply(t_pylst *redirections_list, void (*func)(t_acb *))
{
	t_redirection_fd	*redirection;
	t_acb				*redir_branch;
	t_pylst				*list_branch;

	while (iter_pylst(redirections_list, (void **)&redirection))
	{
		if (ft_strequ(redirection->type, "HEREDOC"))
		{
			list_branch = redirection->heredoc_ast->list_branch;
			while (iter_pylst(list_branch, (void **)&redir_branch))
				func(redir_branch);
		}
	}
}
