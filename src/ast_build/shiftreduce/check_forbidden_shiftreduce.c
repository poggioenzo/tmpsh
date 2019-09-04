/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check_forbidden_shiftreduce.c                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: epoggio <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/27 19:57:18 by epoggio      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/27 20:00:53 by epoggio     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "tmpsh.h"
#include "libft.h"
#include "tokenizer_utils.h"
#include "tagstokens.h"

static	t_bool	cond_check_forbidden_shiftreduce(char *key, size_t i,\
		t_pylst *instack,\
		t_pylst *tags)
{
	size_t	index_forbidden;
	t_pylst	*forbidden_node;

	if (in_reverse(key, "FORBIDDEN"))
	{
		index_forbidden = i - len_pylst(instack);
		forbidden_node = index_pylst(tags, index_forbidden);
		if (ft_strequ("SPACES", (char *)forbidden_node->value))
			forbidden_node = index_pylst(tags, --index_forbidden);
		forbidden_node->value = "FORBIDDEN";
		return (TRUE);
	}
	return (FALSE);
}

/*
** check_forbidden_shiftreduce:
**
** Params:
** @tags: list or stack of tags to check.
**
** Find forbidden pattern in a list of tags.
** The first tag composing the forbidden pattern is change
** to forbidden.
*/

t_bool			check_forbidden_shiftreduce(t_pylst *tags)
{
	size_t	i;
	size_t	len_tags;
	t_pylst	*instack;
	char	*key;

	i = -1;
	len_tags = len_pylst(tags);
	instack = NULL;
	while (++i < (len_tags + 1))
	{
		key = join_pylst(instack, " ");
		if (cond_check_forbidden_shiftreduce(key, i, instack, tags))
			return (free_pylst(&instack, ft_strdel_out(&key, FALSE)));
		else if (i < len_tags && !ft_strequ("SPACES", \
					(char *)vindex_pylst(tags, i)))
		{
			if (!ops_begin_with(key, \
						search_value(g_grammar->grammar, "FORBIDDEN")))
				free_pylst(&instack, 42);
			push_pylst(&instack, vindex_pylst(tags, i), 0, _ptr);
		}
		ft_strdel(&key);
	}
	return (free_pylst(&instack, TRUE));
}
