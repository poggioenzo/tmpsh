/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   strip_tagstokens.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: epoggio <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/17 16:35:36 by epoggio      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/17 16:37:04 by epoggio     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "tagstokens.h"

/*
** strip_tagstokens:
**
** @self: actual tagstokens.
**
** Strip tags and tokens at the begin and the end of self
** if first or last equals SPACES.
*/

void	strip_tagstokens(t_tagstokens *self)
{
	if (self->length > 0 && \
		ft_strequ((char *)vindex_pylst(self->tags, 0), "SPACES"))
		delitems_tagstokens(self, 0, 1, TRUE);
	if (self->length > 0 && \
		ft_strequ((char *)vindex_pylst(self->tags, -1), "SPACES"))
		delitems_tagstokens(self, -1, self->length, TRUE);
}
