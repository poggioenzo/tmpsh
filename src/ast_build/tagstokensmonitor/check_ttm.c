/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check_ttm.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: epoggio <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/03 22:15:36 by epoggio      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/28 09:57:37 by epoggio     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ttm.h"

/*
** check_ttm:
**
** description:
** While the next tag and token are valid we send it to op_selector dispatcher.
**
** parameter:
** - (t_tags_tokens_monitor*) self : actual tagstokensmonitor.
*/

void	check_ttm(t_tags_tokens_monitor *self)
{
	while (next_ttm(self))
		op_selector_ttm(self);
}
