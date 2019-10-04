/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   is_quote_ttm.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: epoggio <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/03 22:32:36 by epoggio      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/03 22:32:47 by epoggio     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ttm.h"

static	void	insert_pylst(t_pylst **here, t_pylst *alias,
							size_t i, t_bool deep)
{
	if (deep)
		replace_pylst(here, pylst_deepcpy(alias), i, i + 1);
	else
		replace_pylst(here, pylst_shacpy(alias), i, i + 1);
}


static void insert_escape(t_tagstokens *tt, int i)
{
		t_pylst *tags;
		t_pylst *tokens;
		char *quote;
		char *escape;

		quote = search_value(g_grammar->grammar, "QUOTE");
		escape = g_grammar->escape;
		tags = NULL;
	 	tokens = NULL;
		push_pylst(&tags, "STMT", 0, _ptr);
		push_pylst(&tags, "END_QUOTE", 0, _ptr);
		push_pylst(&tokens, ft_strdup(escape),
									(ft_strlen(escape) + 1) * sizeof(char), _chare);
		push_pylst(&tokens, ft_strdup(quote),
									(ft_strlen(quote) + 1) * sizeof(char), _chare);
		insert_pylst(&tt->tokens, tokens, i, TRUE);
		insert_pylst(&tt->tags, tags, i, FALSE);
}


/*
** is_quote_ttm:
**
** description:
** Until QUOTE is closed transform all tags in STMT.
**
** parameter:
** - (t_tags_tokens_monitor*) self : actual tagstokensmonitor.
*/

void	is_quote_ttm(t_tags_tokens_monitor *self)
{
	t_bool		inquote;

	inquote = true;
	while (inquote && next_ttm(self, false))
	{
		if (ft_strequ(self->tag, "QUOTE"))
		{
			update_pylst(self->tt->tags, self->i, "END_QUOTE", 0, _ptr);
			inquote = false;
		}
		else
		{
			if (ft_strequ(self->token, "\\'"))
			{
				insert_escape(self->tt, self->i);
				inquote = false;
			}
			else
				update_pylst(self->tt->tags, self->i, "STMT", 0, _ptr);
		}
	}
}
