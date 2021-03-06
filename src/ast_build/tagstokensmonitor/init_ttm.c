/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   init_ttm.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: epoggio <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/03 22:17:53 by epoggio      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/28 09:58:28 by epoggio     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ttm.h"

/*
** init_ttm:
**
** description:
** Instanciate a tagstokensmonitor then check its tagstokens then kill himself.
** Such a suicide.
**
** parameter:
** - (t_tagstokens*) tagstokens : tagstokens to monitoring.
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
	free_pylst(&self->opened, 0);
	ft_memdel((void **)&self);
}
