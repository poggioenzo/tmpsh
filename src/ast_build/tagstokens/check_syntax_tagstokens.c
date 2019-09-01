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

static int		end_escape(char *last_token)
{
	int		len_token;

	len_token = ft_strlen(last_token);
	return (len_token > 0 && *g_grammar->escape == last_token[len_token - 1]);
}

static int		check_incomplete(void)
{
	t_heredocs	*heredoc;

	while (iter_pylst(g_heredocs, (void **)&heredoc))
	{
		if (!(heredoc->closed && !heredoc->tagstokens->incomplete))
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

t_tagstokens	*check_syntax_tagstokens(t_tagstokens *self)
{
	init_ttm(self);

	if (self->valid)
	{
		tagstokens_shiftreduce(self);
		if (self->length > 0 && end_escape(vindex_pylst(self->tokens, -1)))
			self->incomplete = true;
	}
	if (len_pylst(g_heredocs) > 0 && self->not_heredocs)
	{
		self->incomplete |= !check_incomplete();
		self->valid &= check_validity();
	}
	clear_stack_tagstokens(self);
	return (self);
}
