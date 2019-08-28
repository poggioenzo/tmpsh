/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   set_subast_type_acb.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: epoggio <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/27 19:34:53 by epoggio      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/27 19:34:56 by epoggio     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "acb.h"

/*
** set_subast_type_acb:
**
** description:
** Update all type of the subast of this branch.
**
** parameter:
** - (t_acb *) self : Actual abstract command branch.
*/

void	set_subast_type_acb(t_acb *self)
{
	t_ast	*current;
	char	*value;
	int		i;

	i = 0;
	while (iter_pylst(self->subcmd_type, (void**)&value))
	{
		current = vindex_pylst(self->subast, i++);
		current->type = value;
	}
}
