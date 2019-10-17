/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check_redirection_acb.c                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: epoggio <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/27 19:24:34 by epoggio      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/27 19:27:58 by epoggio     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "acb.h"

static  t_tagstokens *get_redirection_tgtk(t_tagstokens *tgtk, int index_red)
{
	int begin;
	t_tagstokens *ret_tagstokens;
	char *tag;

	begin = index_red;
	tag = vindex_pylst(tgtk->tags, index_red + 1);
	if (ft_strequ(tag, "SPACES"))
		index_red += 1;
	index_red += 1;
	while (index_red < (int)tgtk->length)
	{
		tag = vindex_pylst(tgtk->tags, index_red);
		if (ft_strequ(tag, "SPACES"))
			break ;
		index_red += 1;
	}
	ret_tagstokens = copy_tagstokens(tgtk, begin + 1, index_red);
	strip_tagstokens(ret_tagstokens);
	delitems_tagstokens(tgtk, begin, index_red, 42);
	return (ret_tagstokens);
}


static	char	*get_source_acb(t_tagstokens *tgtk, size_t lentags)
{
	char	*source;

	source = NULL;
	if (lentags > 0
			&& digitstr(vindex_pylst(tgtk->tokens, lentags - 1))
			&& !ft_strequ(vindex_pylst(tgtk->tags, lentags - 1), "SUBAST"))
	{
		if (lentags - 2 > 0 &&
			in(find_prev_token(tgtk, lentags - 2, false), "TRUNC_TO_FD",
				"READ_FROM_FD", NULL))
			source = NULL;
		else
			source = ft_strdup(vindex_pylst(tgtk->tokens, lentags - 1));
	}
	return (source);
}

static	int		del_source_red(t_tagstokens *tgtk, int lentags, char **source)
{
	int	begin;

	if (*source)
	{
		begin = find_prev_ind_token(tgtk, lentags - 1);
		delitems_tagstokens(tgtk, begin, begin + 1, 42);
	}
	*source = NULL;
	return (tgtk->length - 1);
}

void			check_redirection_acb(t_acb *self)
{
	int		lentags;
	char	*tag;
	char	*src;

	lentags = (int)self->tagstokens->length;
	while (--lentags >= 0)
	{
		tag = vindex_pylst(self->tagstokens->tags, lentags);
		if (in_grammar(tag, "REDIRECTION"))
		{
			src = get_source_acb(self->tagstokens, lentags);
			push_pylst(&self->redirectionfd,
					init_redfd(
					get_redirection_tgtk(self->tagstokens, lentags),
						tag, src), -1, _redfd);
			lentags = del_source_red(self->tagstokens, lentags, &src);
		}
	}
	strip_tagstokens(self->tagstokens);
	reverse_pylst(&self->redirectionfd);
}
