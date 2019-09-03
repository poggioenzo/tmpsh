/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   free_redfd.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: epoggio <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/03 21:53:22 by epoggio      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/03 21:53:58 by epoggio     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "redirectionfd.h"
#include "ast.h"

void	free_redfd(t_redirection_fd **self)
{
	if (self && *self)
	{
		free_tagstokens(&(*self)->tagstokens, 42);
		if ((*self)->print)
			ft_strdel(&(*self)->print);
		if ((*self)->heredoc_ast)
			free_ast(&(*self)->heredoc_ast);
		ft_memdel((void **)self);
	}
}

void	free_redfd_type(void *redfd)
{
	free_redfd((t_redirection_fd **)redfd);
}
