/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check_redirection_acb.c                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: epoggio <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/27 19:24:34 by epoggio      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/17 13:24:44 by simrossi    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "acb.h"

static t_tagstokens	*get_redirection_tgtk(t_tagstokens *tgtk, int index_red)
{
	int				begin;
	t_tagstokens	*ret_tagstokens;
	char			*tag;

	begin = index_red;
	tag = vindex_pylst(tgtk->tags, index_red + 1);
	if (ft_strequ(tag, "SPACES"))
		index_red += 1;
	index_red += 1;
	while (index_red < (int)tgtk->length)
	{
		tag = vindex_pylst(tgtk->tags, index_red);
		if (ft_strequ(tag, "SPACES") || in_grammar(tag, "REDIRECTION")
			|| in_grammar(tag, "ABS_TERMINATOR"))
			break ;
		index_red += 1;
	}
	ret_tagstokens = copy_tagstokens(tgtk, begin + 1, index_red);
	strip_tagstokens(ret_tagstokens);
	delitems_tagstokens(tgtk, begin, index_red, 42);
	return (ret_tagstokens);
}

static char			*get_source_acb(t_tagstokens *tgtk, size_t i)
{
	char	*source;

	source = NULL;
	if (i > 0
			&& digitstr(vindex_pylst(tgtk->tokens, i - 1))
			&& !ft_strequ(vindex_pylst(tgtk->tags, i - 1), "SUBAST"))
	{
		if (i - 2 > 0 &&
			in(find_prev_token(tgtk, i - 2, false), "TRUNC_TO_FD",
				"READ_FROM_FD", NULL))
			source = NULL;
		else
			source = ft_strdup(vindex_pylst(tgtk->tokens, i - 1));
	}
	return (source);
}

static void			del_source_red(t_tagstokens *tgtk, int i, char **source)
{
	int	begin;

	if (*source)
	{
		begin = find_prev_ind_token(tgtk, i - 1);
		delitems_tagstokens(tgtk, begin, begin + 1, 42);
	}
	*source = NULL;
}

void				check_redirection_acb(t_acb *self)
{
	size_t	i;
	char	*tag;
	char	*src;

	i = 0;
	while (i < self->tagstokens->length)
	{
		tag = vindex_pylst(self->tagstokens->tags, i);
		if (in_grammar(tag, "REDIRECTION"))
		{
			src = get_source_acb(self->tagstokens, i);
			push_pylst(&self->redirectionfd,
					init_redfd(
					get_redirection_tgtk(self->tagstokens, i),
						tag, src), -1, _redfd);
			del_source_red(self->tagstokens, i, &src);
			i--;
		}
		i++;
	}
}
