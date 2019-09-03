/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   copy_tagstokens.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: epoggio <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/17 21:18:31 by epoggio      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/17 21:18:48 by epoggio     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "tagstokens.h"

/*
** copy_tagstokens:
**
** @self: tagstokens to copy.
** @form: first element to copy.
** @to: last element to go for copy (not include).
**
** Return a new allocated tagstokens with all tags and tokens in the
** interval [from:to[ from tagstokens self.
*/

t_tagstokens	*copy_tagstokens(t_tagstokens *self, int from, int to)
{
	t_tagstokens *copy;

	init_tagstokens(&copy, NULL, NULL);
	if (from == to)
	{
		push_pylst(&copy->tokens, "", sizeof(char), _chare);
		push_pylst(&copy->tags, "STMT", 0, _ptr);
	}
	else
	{
		copy->tokens = slice_pylst(self->tokens, from, to);
		copy->tags = slice_pylst(self->tags, from, to);
	}
	update_length_tagstokens(copy);
	return (copy);
}
