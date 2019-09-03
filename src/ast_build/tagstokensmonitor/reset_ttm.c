/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   reset_ttm.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: epoggio <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/03 22:34:18 by epoggio      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/03 22:34:39 by epoggio     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ttm.h"

/*
** reset_ttm:
**
** description:
** Reset g_passed_alias and begin_cmd.
**
** parameter:
** - (t_tags_tokens_monitor*) self : actual tagstokensmonitor.
*/

void	reset_ttm(t_tags_tokens_monitor *self)
{
	self->begin_cmd = TRUE;
	free_pylst(&g_passed_alias, 42);
}

/*
** reset_ttm_out:
**
** description:
** Reset g_passed_alias and begin_cmd then return the out status.
** Yes this is a norm compliant and convenient function.
**
** parameter:
** - (t_tags_tokens_monitor*) self : actual tagstokensmonitor.
** - (int) out : returned status.
*/

int		reset_ttm_out(t_tags_tokens_monitor *self, int out)
{
	reset_ttm(self);
	return (out);
}
