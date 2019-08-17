/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tagstokens.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: epoggio <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/16 16:50:43 by epoggio      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/17 16:42:14 by epoggio     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "tagstokens.h"

void	init_tagstokens(t_tagstokens **self, t_pylst *tokens, t_pylst *tags)
{
	*self = (t_tagstokens*)ft_memalloc(sizeof(t_tagstokens));
	(*self)->tokens = tokens;
	(*self)->tags = tags;
	(*self)->stack = NULL;
	(*self)->token_error = NULL;
	(*self)->valid = TRUE;
	(*self)->incomplete = FALSE;
	(*self)->length = 0;
	(*self)->iter = -1;
	update_length_tagstokens(*self);
}
