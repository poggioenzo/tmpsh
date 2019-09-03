/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   init_ttm.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: epoggio <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/03 22:17:53 by epoggio      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/03 22:18:04 by epoggio     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ttm.h"

/*
** init_ttm:
**
** description:
** describe what you function do.
**
** parameter:
** - (t_tags_tokens_monitor*) self : actual tagstokensmonitor.
*/

void	init_ttm(t_tagstokens *tagstokens)
{
	t_tags_tokens_monitor *self;

	self = (t_tags_tokens_monitor*)ft_memalloc(sizeof(t_tags_tokens_monitor));
	self->tt = tagstokens;
	self->i = -1;
	self->begin_cmd = TRUE;
	push_pylst(&self->opened, " ", 0, _ptr);
	check_ttm(self);
	free_pylst(&self->heredocs_keys, 0);
	free_pylst(&self->opened, 0);
	ft_memdel((void **)&self);
}
