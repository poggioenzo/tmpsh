/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check_syntax_tagstokens.c                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: epoggio <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/27 20:12:36 by epoggio      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/27 20:14:15 by epoggio     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "tagstokens.h"

void	check_syntax_tagstokens(t_tagstokens *self)
{
	if (self->valid)
		tagstokens_shiftreduce(self);
}
