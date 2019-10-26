/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   in_redirection_ttm.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: epoggio <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/03 22:16:59 by epoggio      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/03 22:17:13 by epoggio     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ttm.h"

/*
** is_redirection_ttm:
**
** description:
** Check if every tokens after a redirection (except HEREDOC[S|MINUS])
** is alright.
**
** parameter:
** - (t_tags_tokens_monitor*) self : actual tagstokensmonitor.
*/

void	in_redirection_ttm(t_tags_tokens_monitor *self)
{
	t_bool		not_end;

	not_end = next_ttm(self);
	if (ft_strequ(self->tag, "SPACES"))
		not_end = next_ttm(self);
	if (not_end && !in_grammar(self->tag, "ABS_TERMINATOR"))
	{
		op_selector_ttm(self);
		self->begin_cmd = true;
	}
	else
	{
		self->tt->valid = false;
		self->tt->token_error = self->token;
	}
	self->begin_cmd = true;
}
