/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   in_sub_process_ttm.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: epoggio <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/03 22:17:26 by epoggio      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/03 22:17:32 by epoggio     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ttm.h"

/*
** is_sub_process_ttm:
**
** description:
** describe what you function do.
**
** parameter:
** - (type) name : what is this param?
**
** return value:
** - (type) value : descibe output.
*/

void	in_sub_process_ttm(t_tags_tokens_monitor *self)
{
	t_bool	in_command;
	char	*exit_tag;

	reset_ttm(self);
	in_command = true;
	push_pylst(&self->opened, self->tag, 0, _ptr);
	exit_tag = search_value(g_grammar->opening_tags, self->tag);
	while (in_command && next_ttm(self, false))
	{
		if (ft_strequ(self->tag, exit_tag))
		{
			pop_pylst(&self->opened, -1);
			in_command = false;
		}
		else
			op_selector_ttm(self);
	}
}
