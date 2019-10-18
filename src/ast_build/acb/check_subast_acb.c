/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check_subast_acb.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: epoggio <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/27 19:30:50 by epoggio      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/27 19:32:25 by epoggio     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "acb.h"

static	void	replace_subast(t_tagstokens *tgtk, size_t begin,
		size_t end, int number)
{
	t_pylst	*tag;
	t_pylst	*token;

	tag = NULL;
	token = NULL;
	push_pylst(&tag, "SUBAST", 0, _ptr);
	push_pylst(&token, ft_itoa(number), NO_COPY_BUT_FREE, _chare);
	replace_pylst(&tgtk->tags, tag, begin, end);
	replace_pylst(&tgtk->tokens, token, begin, end);
	update_length_tagstokens(tgtk);
}

/*
** check_subast_acb:
**
** description:
** Check if there is subast in command. If it's the case create an new
** ast to ge deepth branch. Do some modification on the tagstokens of the
** branch.
**
** parameter:
** - (t_acb *) self : Actual abstract command branch.
*/

void			check_subast_acb(t_acb *self)
{
	size_t	i;
	size_t	begin;
	char	*tag;

	i = 0;
	while (i < self->tagstokens->length)
	{
		tag = vindex_pylst(self->tagstokens->tags, i);
		if (search_value(g_grammar->opening_tags, tag))
		{
			begin = i + 1;
			push_pylst(&self->subcmd_type, tag, 0, _ptr);
			i = skip_openning_tagstokens(self->tagstokens, i, NULL) - 1;
			push_pylst(&self->subast, init_ast(
					copy_tagstokens(self->tagstokens, begin, i)), -1, _ast);
			replace_subast(self->tagstokens, begin - 1, i + 1, \
					len_pylst(self->subast) - 1);
			i = begin - 1;
		}
		i++;
	}
}
