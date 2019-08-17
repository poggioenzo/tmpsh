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

void	strip_tagstokens(t_tagstokens *self)
{
	if (self->length > 0 && \
		ft_strequ((char *)get_value_pylst(self->tags, 0), "SPACES"))
		delitems_tagstokens(self, 0, 1, TRUE);
	if (self->length > 0 && \
		ft_strequ((char *)get_value_pylst(self->tags, -1), "SPACES"))
		delitems_tagstokens(self, -1, self->length, TRUE);
	if (self->length == 1 && \
		ft_strequ((char *)get_value_pylst(self->tags, 0), "SPACES"))
	{
		free_pylst(&self->tags, 42);
		free_pylst(&self->tokens, 42);
	}
}
