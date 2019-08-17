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

/*
** delitems_tagstokens:
**
** @self: actual tagstokens.
** @start: index of the first element to delete.
** @end: index until it deletes.
** @status: value to return.
**
** Delete tags and tokens of self according at from and to.
*/

int		delitems_tagstokens(t_tagstokens *self, int from, int to, int status)
{
	del_portion_pylst(&self->tokens, from, to);
	del_portion_pylst(&self->tags, from, to);
	update_length_tagstokens(self);
	return (status);
}
