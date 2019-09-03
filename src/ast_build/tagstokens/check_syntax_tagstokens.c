/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check_syntax_tagstokens.c                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: epoggio <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/27 20:12:36 by epoggio      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/03 21:50:53 by epoggio     ###    #+. /#+    ###.fr     */
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
	t_bool		ret;

	ret = false;
	while (iter_pylst(g_heredocs, (void **)&heredoc) && !ret)
		ret |= !(heredoc->closed && !heredoc->tagstokens->incomplete);
	return (ret);
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

static void		remove_escape_stmt(t_tagstokens *self)
{
	char *tag;
	char *token;

	while (iter_tagstokens(self, &token, &tag))
	{
		if (ft_strequ(tag, "STMT") && ft_strlen(token) > 1 && token[0] == '\\')
			ft_strcpy(token, token + 1);
	}
}

t_tagstokens	*check_syntax_tagstokens(t_tagstokens *self)
{
	init_ttm(self);
	remove_escape_stmt(self);
	if (self->valid)
	{
		tagstokens_shiftreduce(self);
		if (self->length > 0 && end_escape(vindex_pylst(self->tokens, -1)))
			self->incomplete = true;
	}
	if (len_pylst(g_heredocs) > 0 && self->not_heredocs)
	{
		self->incomplete |= check_incomplete();
		self->valid &= check_validity();
	}
	clear_stack_tagstokens(self);
	return (self);
}
