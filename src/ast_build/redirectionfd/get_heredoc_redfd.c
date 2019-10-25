/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_heredoc_redfd.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: epoggio <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/27 19:50:36 by epoggio      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/27 19:51:03 by epoggio     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "redirectionfd.h"
#include "ast.h"

/*
** get_heredoc_redfd:
**
** description:
** This actual redirection is an Heredoc. This function affect the good pointer
** of the tagstokens containing the heredoc.
**
** parameter:
** - (t_redirection_fd) self : the actual redirection structure.
*/

int	get_heredoc_redfd(t_redirection_fd *self)
{
	t_heredocs		*heredoc;

	if (len_pylst(g_heredocs) > 0)
	{
		heredoc = pop_pylst(&g_heredocs, 0);
		self->heredoc_ast = init_ast(heredoc->tagstokens);
		free_heredocs(&heredoc, 42);
	}
	return (0);
}
