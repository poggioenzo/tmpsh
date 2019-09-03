/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   is_quote_ttm.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: epoggio <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/03 22:32:36 by epoggio      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/03 22:32:47 by epoggio     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ttm.h"

/*
** is_quote_ttm:
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

void	is_quote_ttm(t_tags_tokens_monitor *self)
{
	t_bool		inquote;

	inquote = true;
	while (inquote && next_ttm(self, false))
	{
		if (ft_strequ(self->tag, "QUOTE"))
		{
			update_pylst(self->tt->tags, self->i, "END_QUOTE", 0, _ptr);
			inquote = false;
		}
		else
			update_pylst(self->tt->tags, self->i, "STMT", 0, _ptr);
	}
}
