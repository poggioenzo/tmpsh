/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   close_heredocs.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: epoggio <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/03 22:05:21 by epoggio      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/03 22:05:24 by epoggio     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heredocs.h"

/*
** close_heredocs:
**
** description:
** describe what you function do.
**
** parameter:
** - (type) name : what is this param?
**
** return value:
** - (type) value : descibe output.
*/

void	close_heredocs(t_heredocs *self)
{
	self->tagstokens = copy_tagstokens(self->tagstokens, 0, -self->len_key);
	self->tagstokens->not_heredocs = false;
	if (self->minus)
		striplines_heredocs(self);
	check_syntax_tagstokens(self->tagstokens);
	self->closed = true;
}
