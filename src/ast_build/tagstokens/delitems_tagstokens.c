/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   delitems_tagstokens.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: epoggio <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/17 16:35:04 by epoggio      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/17 16:35:25 by epoggio     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "tagstokens.h"

int		delitems_tagstokens(t_tagstokens *self, int start, int stop, int status)
{
	del_portion_pylst(&self->tokens, start, stop);
	del_portion_pylst(&self->tags, start, stop);
	update_length_tagstokens(self);
	return (status);
}
