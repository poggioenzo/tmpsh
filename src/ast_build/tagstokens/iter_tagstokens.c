/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   iter_tagstokens.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: epoggio <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/16 12:38:33 by epoggio      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/27 20:19:30 by epoggio     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "tagstokens.h"

/*
** break_tagstokens:
**
** @self: choosen list.
**
** Reset tagstokens iterator.
*/

void	break_tagstokens(t_tagstokens *self)
{
	self->iter = -1;
}

/*
** break_tagstokens:
**
** @self: choosen list.
** @status: given status.
**
** Reset tagstokens iterator and return status.
** You may want instead of use break statement use
** `return break_out_tagstokens(tt, status);`
*/

int		break_out_tagstokens(t_tagstokens *self, int status)
{
	self->iter = -1;
	return (status);
}

/*
** iter_tagstokens:
**
** Arguments, in order :
** @self: choosen tagstokens.
** @token: adress of pointer for token.
** @tag: adress of pointer for tag.
**
** Iter on tagstokens length. Change adress of token and tag
** if it's still some iteration. If the case return True else
** reset iterator and return False.
*/

t_bool	iter_tagstokens(t_tagstokens *self, char **token, char **tag)
{
	self->iter++;
	if (self->iter < (int)self->length)
	{
		*token = (char *)get_value_pylst(self->tokens, self->iter);
		*tag = (char *)get_value_pylst(self->tags, self->iter);
		return (TRUE);
	}
	self->iter = -1;
	return (FALSE);
}
