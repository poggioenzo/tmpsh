/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   is_abs_terminator_ttm.c                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: epoggio <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/03 22:18:21 by epoggio      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/03 22:18:30 by epoggio     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ttm.h"

/*
** is_abs_terminator_ttm:
**
** description:
** Maybe in the dispatcher we can put reset_ttm directly lol.
** If it's an abstact terminator do a reset.
**
** parameter:
** - (t_tags_tokens_monitor*) self : actual tagstokensmonitor.
*/

void	is_abs_terminator_ttm(t_tags_tokens_monitor *self)
{
	reset_ttm(self);
}
