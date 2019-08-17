/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   update_length_tagstokens.c                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: epoggio <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/17 16:35:53 by epoggio      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/17 16:35:56 by epoggio     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "tagstokens.h"

void	update_length_tagstokens(t_tagstokens *self)
{
	self->length = len_pylst(self->tokens);
}
