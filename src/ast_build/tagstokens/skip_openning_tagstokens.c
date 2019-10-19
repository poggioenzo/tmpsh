/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   skip_openning_tagstokens.c                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: epoggio <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/27 20:23:38 by epoggio      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/27 20:24:55 by epoggio     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "tagstokens.h"

/*
** skip_openning_tagstokens:
**
** @self: actual tagstokens.
** @i: actual index in tagstokens.
** @until: tag to break if find or NULL.
**
** Find the end index of an opened operator and return it.
** If until is define return the index when it first appears.
*/

int	skip_openning_tagstokens(t_tagstokens *self, size_t i, char *until)
{
	t_pylst	*stack;
	char	*tag;
	char	*end_tag;

	stack = NULL;
	tag = (char *)vindex_pylst(self->tags, i++);
	push_pylst(&stack, search_value(g_grammar->opening_tags, tag), 0, _ptr);
	while (i < self->length)
	{
		tag = (char *)vindex_pylst(self->tags, i);
		if (!(stack) || (until && ft_strequ(until, tag)))
			break ;
		else if ((end_tag = search_value(g_grammar->opening_tags, tag)))
			push_pylst(&stack, end_tag, 0, _ptr);
		else if (ft_strequ(tag, (char *)vindex_pylst(stack, -1)))
			del_portion_pylst(&stack, -1, len_pylst(stack));
		i++;
	}
	return (free_pylst(&stack ,i));
}
