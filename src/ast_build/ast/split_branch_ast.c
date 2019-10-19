/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   split_branch_ast.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: epoggio <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/27 19:42:03 by epoggio      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/27 19:48:57 by epoggio     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ast.h"

static	int	update_begin(int i, char **and_or_begin)
{
	*and_or_begin = "";
	return (i + 1);
}

static	void init_var(size_t *i, size_t *begin, char **and_or_begin)
{
	*i = 0;
	*begin = 0;
	*and_or_begin = "";
}

void		split_branch_ast(t_ast *self, t_tagstokens *tgtk)
{
	size_t	i;
	size_t	begin;
	char	*and_or_begin;
	char	*tag;
	t_tagstokens *tmp;

	init_var(&i, &begin, &and_or_begin);
	while (i <= tgtk->length)
	{
		tag = (i < tgtk->length) ? vindex_pylst(tgtk->tags, i) : "";
		if (search_value(g_grammar->opening_tags, tag))
			i = skip_openning_tagstokens(tgtk, i, "\0") - 1;
		else if (in_grammar(tag, "ABS_TERMINATOR")
				|| (i == tgtk->length && begin != i))
		{
			tmp = copy_tagstokens(tgtk, begin, i);
			push_pylst(&self->list_branch,
				init_acb(tmp, and_or_begin, tag), -1, _acb);
			begin = update_begin(i, &and_or_begin);
		//free_tagstokens(&tmp, 42); // plus rien ne marche avec
		}
		if (!(++i) || ft_strequ(tag, "CMDAND") || ft_strequ(tag, "CMDOR"))
			and_or_begin = tag;
	}
}
