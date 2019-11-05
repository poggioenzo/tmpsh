/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   is_dquotes_ttm.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: epoggio <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/03 22:18:52 by epoggio      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/05 14:55:25 by epoggio     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ttm.h"

static	void	escaped_chare(char *locale_stmt)
{
	if (ft_strlen(locale_stmt) > 1 && ft_incharset(locale_stmt[1], "$`\"\\\n"))
		ft_strcpy(locale_stmt, locale_stmt + 1);
}

/*
** is_dquotes_ttm:
**
** description:
** Until DQUOTES is closed will transform all tags in STMT.
** Except for special tags inside dquotes_opening_tags.
**
** parameter:
** - (t_tags_tokens_monitor*) self : actual tagstokensmonitor.
*/

void			is_dquotes_ttm(t_tags_tokens_monitor *self)
{
	t_bool	indquote;
	char	*new_str;

	indquote = true;
	push_pylst(&self->opened, "DQUOTES", 0, _ptr);
	while (indquote && next_ttm(self))
	{
		if (ft_strequ(self->tag, "DQUOTES") && \
				ft_strequ(vindex_pylst(self->opened, -1), "DQUOTES"))
		{
			pop_pylst(&self->opened, -1);
			update_pylst(self->tt->tags, self->i, "END_DQUOTES", 0, _ptr);
			indquote = false;
		}
		else if (search_value(g_grammar->dquotes_opening_tags, self->tag))
			op_selector_ttm(self);
		else
		{
			if (ft_strequ(vindex_pylst(self->tt->tags, self->i), "STMT"))
				escaped_chare(vindex_pylst(self->tt->tokens, self->i));
			new_str = !ft_strequ(vindex_pylst(self->tt->tags, self->i), "VAR") ?
				"STMT" : "VAR";
			update_pylst(self->tt->tags, self->i, new_str, 0, _ptr);
		}
	}
}
