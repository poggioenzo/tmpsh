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

static	char	*get_source_acb(t_tagstokens *tgtk, size_t lentags, char *tag)
{
	char	*source;

	source = NULL;
	if (lentags > 0
			&& digitstr(find_prev_token(tgtk, lentags - 1, TRUE))
			&& !ft_strequ(find_prev_token(tgtk, lentags - 1, FALSE), "SUBAST")
			&& !ft_strequ(tag, "HEREDOC")
			&& !ft_strequ(tag, "TRIPLEHEREDOC")
			&& !ft_strequ(tag, "HEREDOCMINUS"))
		source = ft_strdup(find_prev_token(tgtk, lentags - 1, TRUE));
	return (source);
}

static	int		del_tgtk_red(t_tagstokens *tgtk, int lentags,
		int previous, char *source)
{
	int	begin;

	delitems_tagstokens(tgtk, previous, previous + 1, 42);
	delitems_tagstokens(tgtk, lentags, lentags + 1, 42);
	if (source)
	{
		begin = find_prev_ind_token(tgtk, lentags - 1);
		delitems_tagstokens(tgtk, begin, begin + 1, 42);
	}
	source = NULL;
	return (tgtk->length - 1);
}

void			check_redirection_acb(t_acb *self)
{
	int		lentags;
	int		previous;
	char	*tag;
	char	*src;

	lentags = (int)self->tagstokens->length;
	while (--lentags >= 0)
	{
		tag = get_value_pylst(self->tagstokens->tags, lentags);
		if (in_pylst_chare(tag,\
					search_value(g_grammar->grammar, "REDIRECTION")))
		{
			src = get_source_acb(self->tagstokens, lentags, tag);
			push_pylst(&self->redirectionfd,
					init_redfd(
					copy_tagstokens(self->tagstokens, previous, previous + 1),
						tag, src), 0, _ptr);
			lentags = del_tgtk_red(self->tagstokens, lentags, previous, src);
		}
		else if (!ft_strequ(tag, "SPACES"))
			previous = lentags;
	}
	strip_tagstokens(self->tagstokens);
	reverse_pylst(&self->redirectionfd);
}
