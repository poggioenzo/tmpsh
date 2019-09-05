/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   is_abs_terminator_ttm.c                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: epoggio <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/03 22:18:21 by epoggio      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/03 22:18:30 by epoggio     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ttm.h"

/*
** is_abs_terminator_ttm:
**
** description:
** Maybe in the dispatcher we can put reset_ttm directly lol.
** If it's an abstact terminator do a reset.
**
** parameter:
** - (t_tags_tokens_monitor*) self : actual tagstokensmonitor.
*/

void	is_abs_terminator_ttm(t_tags_tokens_monitor *self)
{
	int to_del;

	if (in_grammar(self->tag, "BINARY")
		&& self->i + 1 < (int)self->tt->length
		&& ft_strequ(find_next_token(self->tt, self->i + 1, false), "NEW_LINE"))
	{
		to_del = find_next_ind_token(self->tt, self->i + 1);
		delitems_tagstokens(self->tt, to_del, to_del + 1, 42);
	}
	reset_ttm(self);
}
