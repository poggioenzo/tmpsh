/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   clear_stack_tagstokens.c                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: epoggio <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/27 20:14:26 by epoggio      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/27 20:15:24 by epoggio     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "tagstokens.h"

/*
** clear_stack_tagstokens:
**
** @self: actual tagstokens.
**
** Remove all CMD string from self->stack.
*/

void	clear_stack_tagstokens(t_tagstokens *self)
{
	char	*str;
	int		*to_delete;
	int		n;
	int		i;

	n = 0;
	i = 0;
	to_delete = (int *)ft_memalloc((len_pylst(self->stack) + 1) * sizeof(int));
	while (iter_pylst(self->stack, (void **)&str))
	{
		if (ft_strequ(str, "CMD") || ft_strequ(str, "COMMAND_SH"))
			to_delete[n++] = i;
		i++;
	}
	while (n--)
		del_portion_pylst(&self->stack, to_delete[n], to_delete[n] + 1);
	ft_memdel((void **)&to_delete);
}
