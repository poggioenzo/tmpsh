/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tagging.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: epoggio <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/17 13:38:16 by epoggio      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/17 13:48:05 by epoggio     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "tmpsh.h"
#include "libft.h"
#include "globals.h"

/*
** get_tag_tagstokens:
**
** @self: tagstokens to attribute
**
** Tag every token already present in self->tokens.
** ! If there is already tags they would be cleared !
*/

void	get_tag_tagstokens(t_tagstokens *self)
{
	int			iter;
	size_t		len_tok;
	char		*tok;

	iter = free_pylst(&self->tags, 0);
	while (iter < self->length)
	{
		tok = (char *)get_value_pylst(self->tokens, iter);
		len_tok = ft_strlen(tok);
		if (in_pylst_chare(tok, g_grammar->leaf_op))
			push_pylst(&(self->tags), \
					search_value(g_grammar->reverse, tok), 0, _ptr);
		else if (ft_strspn(tok, g_grammar->spaces) == len_tok)
			push_pylst(&(self->tags), "SPACES", 0, _ptr);
		else if (len_tok > 1 && tok[0] == '$')
			push_pylst(&(self->tags), "VAR", 0, _ptr);
		else
			push_pylst(&(self->tags), "STMT", 0, _ptr);
		iter++;
	}
	// strip()
	// update_length()
}
