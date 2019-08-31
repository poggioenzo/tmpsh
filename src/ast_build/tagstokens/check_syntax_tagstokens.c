/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check_syntax_tagstokens.c                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: epoggio <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/27 20:12:36 by epoggio      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/27 20:14:15 by epoggio     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "tagstokens.h"

static int		check_incomplete(void)
{
	t_heredocs	*heredoc;

	while (iter_pylst(g_heredocs, (void **)&heredoc))
	{
		if (!(heredoc->closed && !heredoc->incomplete))
			return (false);
	}
	return (true);
}

static int		check_validity(void)
{
	t_heredocs	*heredoc;

	while (iter_pylst(g_heredocs, (void **)&heredoc))
	{
		if (!heredoc->tagstokens->valid)
			return (false);
	}
	return (true);
}

void	check_syntax_tagstokens(t_tagstokens *self)
{
	init_ttm(self);
	if (self->valid)
	{
		tagstokens_shiftreduce(self);
		if (self->length > 0 && end_escape(vindex_pylst(self->tokens, -1)))
			self->incomplete = true;
	}
	if (len_pylst(g_heredocs) > 0 && self->not_heredoc)
	{
		self->incomplete |= !check_incomplete();
		self->valid &= check_validity();
	}
	clear_stack(self);
	return (self);
}
