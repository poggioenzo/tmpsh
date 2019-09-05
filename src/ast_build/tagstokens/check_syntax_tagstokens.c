/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check_syntax_tagstokens.c                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: epoggio <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/27 20:12:36 by epoggio      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/04 16:42:27 by epoggio     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "tagstokens.h"

static int		end_escape(char *last_token)
{
	t_bool	ret;

	ret = ft_strlen(last_token) == 2;
	ret &= last_token[0] == g_grammar->escape[0];
	ret &= (int)last_token[1] == 10;
	return (ret);
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
		{
			ft_strcpy(token, token + 1);
			if (ft_strequ(token, "\n"))
				update_pylst(self->tags, self->iter, "SPACES", 0, _ptr);
		}
	}
}

t_tagstokens	*check_syntax_tagstokens(t_tagstokens *self)
{
	t_bool not_ended;

	not_ended = self->length > 0 && end_escape(vindex_pylst(self->tokens, -1));
	remove_escape_stmt(self);
	strip_tagstokens(self);
	init_ttm(self);
	if (self->valid)
	{
		tagstokens_shiftreduce(self);
		if (not_ended)
			self->incomplete = true;
	}
	if (len_pylst(g_heredocs) > 0 && self->not_heredocs)
	{
		self->incomplete |= check_incomplete();
		self->valid &= check_validity();
	}
	clear_stack_tagstokens(self);
	if (self->token_error && ft_strequ(self->token_error, "\n"))
	{
		ft_strdel(&self->token_error);
		self->token_error = ft_strdup("'\\n'");
	}
	return (self);
}
