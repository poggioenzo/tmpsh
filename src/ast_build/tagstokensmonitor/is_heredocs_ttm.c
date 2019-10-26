/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   is_heredocs_ttm.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: epoggio <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/03 22:19:28 by epoggio      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/22 17:32:25 by simrossi    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ttm.h"

static char		*transform_end_tag(char *tag)
{
	if (ft_strequ(tag, "QUOTE"))
		tag = "END_QUOTE";
	if (ft_strequ(tag, "DQUOTES"))
		tag = "END_DQUOTES";
	return (tag);
}

static void		append_to_heredocs(t_tags_tokens_monitor *self, char *key,
									int len, t_bool quoted)
{
	t_heredocs *hd;

	hd = NULL;
	init_heredocs(&hd, key, len, quoted);
	push_pylst(&g_heredocs, hd, 0, _heredocs);
}

static void		append_to_heredocs_composed_keys(t_tags_tokens_monitor *self)
{
	t_pylst	*list_tok;
	int		j;

	j = skip_openning_tagstokens(self->tt, self->i,
								get_end_tag(self->tag));
	list_tok = slice_pylst(self->tt->tokens, self->i + 1, j - 1);
	self->i = j;
	update_pylst(self->tt->tags, self->i,
				transform_end_tag(vindex_pylst(self->tt->tags, self->i))
				, 0, _ptr);
	append_to_heredocs(self, join_pylst(list_tok, ""),
			len_pylst(list_tok), true);
	free_pylst(&list_tok, 42);
}

static void		set_false(t_tags_tokens_monitor *self)
{
	self->tt->valid = false;
	self->tt->token_error = ft_strdup(self->token);
}

/*
** is_heredocs_ttm:
**
** description:
** Push to self->heredocs_keys all information to do correctly the future
** incoming heredoc inside the global g_heredoc.
**
** parameter:
** - (t_tags_tokens_monitor*) self : actual tagstokensmonitor.
*/

void			is_heredocs_ttm(t_tags_tokens_monitor *self)
{
	t_bool	not_end;

	not_end = next_ttm(self);
	if (ft_strequ(self->tag, "SPACES"))
		not_end = next_ttm(self);
	if (not_end && !in_grammar(self->tag, "ABS_TERMINATOR"))
	{
		if (search_value(g_grammar->opening_tags, self->tag))
		{
			if (in(self->tag, "QUOTE", "DQUOTES", NULL))
				append_to_heredocs_composed_keys(self);
			else
				set_false(self);
		}
		else
			append_to_heredocs(self, ft_strdup(self->token), 1, false);
	}
	else
		set_false(self);
	self->begin_cmd = true;
}
