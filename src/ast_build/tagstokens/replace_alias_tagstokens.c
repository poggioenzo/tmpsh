/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   replace_alias_tagstokens.c                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: epoggio <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/27 20:20:46 by epoggio      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/27 20:23:03 by epoggio     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "tagstokens.h"

static	void	insert_alias(t_pylst **here, t_pylst *alias,
							size_t i, t_bool deep)
{
	if (deep)
		replace_pylst(here, pylst_deepcpy(alias), i, i + 1);
	else
		replace_pylst(here, pylst_shacpy(alias), i, i + 1);
}

/*
** replace_alias_tagstokens:
**
** @self: actual tagstokens.
** @alias_input: input alias to transform.
** @i: index where insert alias tags and tokens.
**
** After tokenise and tag the result of the alias, the tokens will be insert
** at the index i with a deepcopy and tags with a shallowcopy.
*/

t_bool			replace_alias_tagstokens(t_tagstokens *self,
										char *alias_key, size_t i)
{
	t_bool			ret;
	t_tagstokens	*tt_alias;
	char 			*alias_result;

	alias_result = search_value(g_alias, alias_key);
	ret = ft_isspace(alias_result[ft_strlen(alias_result) - 1]);
	if (in_pylst_chare(alias_key, g_actual_alias))
	{
		ret = false;
		alias_result = alias_key;
	}
	push_pylst(&g_actual_alias, alias_key, 0, _ptr);
	input_init_tagstokens(&tt_alias, alias_result);
	g_aliasindepth = tt_alias->length + i + 1;
	insert_alias(&self->tokens, tt_alias->tokens, i, TRUE);
	insert_alias(&self->tags, tt_alias->tags, i, FALSE);
	self->valid = tt_alias->valid;
	update_length_tagstokens(self);
	free_tagstokens(&tt_alias, TRUE);
	return (ret);
}
