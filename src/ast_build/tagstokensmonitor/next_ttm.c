/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   next_ttm.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: epoggio <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/03 22:32:57 by epoggio      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/03 22:33:44 by epoggio     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ttm.h"

/*
** next_ttm:
**
** description:
** Set new tag and token in function of the present index and length.
** If clear param is true remove tag and token of the tagstokens.
**
** parameter:
** - (t_tags_tokens_monitor*) self : actual tagstokensmonitor.
** - (t_bool*) clear : boolean to remove element.
*/

t_bool	next_ttm(t_tags_tokens_monitor *self) //, t_bool clear)
{
	t_bool	ret;

	self->i++;
	ret = self->i < (int)self->tt->length;
	if (ret)
	{
		self->tag = vindex_pylst(self->tt->tags, self->i);
		self->token = vindex_pylst(self->tt->tokens, self->i);
		
	}
	return (ret);
}
