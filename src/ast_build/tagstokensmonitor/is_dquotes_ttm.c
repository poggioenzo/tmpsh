/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   is_dquotes_ttm.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: epoggio <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/03 22:18:52 by epoggio      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/17 14:19:21 by simrossi    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ttm.h"

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

void	is_dquotes_ttm(t_tags_tokens_monitor *self)
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
			new_str = !ft_strequ(vindex_pylst(self->tt->tags, self->i), "VAR") ?
				"STMT" : "VAR";
			update_pylst(self->tt->tags, self->i, new_str, 0, _ptr);
		}
	}
}
