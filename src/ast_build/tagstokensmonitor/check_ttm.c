/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check_ttm.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: epoggio <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/03 22:15:36 by epoggio      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/03 22:15:48 by epoggio     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ttm.h"

/*
** check_ttm:
**
** description:
** describe what you function do.
**
** parameter:
** - (t_tags_tokens_monitor*) self : actual tagstokensmonitor.
*/

void	check_ttm(t_tags_tokens_monitor *self)
{
	while (next_ttm(self, false))
		op_selector_ttm(self);
}
