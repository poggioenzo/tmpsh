/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   free_tagstokens.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: epoggio <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/27 20:18:12 by epoggio      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/27 20:18:56 by epoggio     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "tagstokens.h"

/*
** free_tagstokens:
**
** @self: adress of tagstokens to free.
** @status: status to return
**
** Free tagstokens and its attributes if they exist.
*/

int	free_tagstokens(t_tagstokens **self, int status)
{
	if (self && *self)
	{
		free_pylst(&(*self)->tokens, status);
		free_pylst(&(*self)->tags, status);
		free_pylst(&(*self)->stack, status);
		if ((*self)->token_error)
			ft_strdel(&(*self)->token_error);
		ft_memdel((void **)self);
	}
	return (status);
}
