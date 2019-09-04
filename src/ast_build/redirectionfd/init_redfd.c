/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   init_redfd.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: epoggio <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/27 19:51:18 by epoggio      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/03 21:52:44 by epoggio     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "redirectionfd.h"

/*
** init_redfd:
**
** description:
** Create, initialise and return an redirection fd.
**
** parameter:
** - (t_tagstokens*) tgtk : tags and tokens which compose the redirection.
** - (char *) type : the type of redirection.
** - (char *) source : string number representation for the source of the
**                     redirection.
**
** return value:
** - (t_redirection_fd*) self: the actual redirection fd.
*/

t_redirection_fd	*init_redfd(t_tagstokens *tgtk, char *type,\
		char *source)
{
	t_redirection_fd	*self;

	self = (t_redirection_fd*)ft_memalloc(sizeof(t_redirection_fd));
	self->tagstokens = tgtk;
	self->type = type;
	self->heredoc_ast = NULL;
	if (!source)
		source = (ft_strequ(self->type, "READ_FROM_FD")\
				|| ft_strequ(self->type, "READ_FROM")) ? "0" : "1";
	self->source = ft_atoi(source);
	self->dest = vindex_pylst(self->tagstokens->tokens,\
			self->tagstokens->length - 1);
	self->close = (ft_strequ(self->type, "READ_FROM_FD")\
	|| ft_strequ(self->type, "TRUNC_TO_FD")) && ft_strequ(self->dest, "-");
	self->error = FALSE;
	if ((ft_strequ(self->type, "HEREDOCMINUS") \
				|| ft_strequ(self->type, "HEREDOC")))
		get_heredoc_redfd(self);
	self->print = str_redfd(self);
	return (self);
}
