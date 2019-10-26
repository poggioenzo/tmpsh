/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   is_braceparam_ttm.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: epoggio <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/03 22:18:38 by epoggio      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/03 22:18:42 by epoggio     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ttm.h"

/*
** is_braceparam_ttm:
**
** description:
** Check the STMT inside braceparam. Not ok STMT create bad substitution error.
**
** parameter:
** - (t_tags_tokens_monitor*) self : actual tagstokensmonitor.
*/

void	is_braceparam_ttm(t_tags_tokens_monitor *self)
{
	t_bool	not_end;
	char	*stmt_tag;

	not_end = next_ttm(self);
	stmt_tag = self->tag;
	not_end = not_end && next_ttm(self);
	if (!ft_strequ(stmt_tag, "STMT") || !ft_strequ(self->tag, "END_BRACE"))
	{
		if (not_end)
		{
			self->tt->valid = false;
			self->tt->token_error = "bad substitution";
		}
	}
}
