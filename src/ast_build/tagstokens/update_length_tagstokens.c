/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   update_length_tagstokens.c                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: epoggio <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/17 16:35:53 by epoggio      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/17 21:19:51 by epoggio     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "tagstokens.h"

/*
** update_length_tagstokens:
**
** @self: actual tagstokens.
**
** Set length of self according to the length pylst tokens.
*/

void	update_length_tagstokens(t_tagstokens *self)
{
	self->length = len_pylst(self->tokens);
}
