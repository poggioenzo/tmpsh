/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   reduce_all_shiftreduce.c                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: epoggio <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/27 20:07:27 by epoggio      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/27 20:07:57 by epoggio     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "tmpsh.h"
#include "libft.h"
#include "globals.h"
#include "shiftreduce.h"

static	t_pylst		**reduce(t_pylst **stack, int instack)
{
	char	*key;

	key = join_pylst(index_pylst(*stack, instack), " ");
	del_portion_pylst(stack, instack, len_pylst(*stack));
	push_pylst(stack, search_value(g_grammar->reverse, key), 0, _ptr);
	ft_strdel(&key);
	return (stack);
}

/*
** reduce_all:
**
** Params:
** @stack: actual list of tags composing the stack.
** @instack: length of the reducable pattern.
** @next_tag: next tag which will may append to stack.
**
** Return the reduced stack. Transformed pattern values
** in pattern keys. While it's possible to transformed
** pattern instead of instack it's transformed.
*/

t_pylst				*reduce_all(t_pylst **stack, int instack, char *next_tag)
{
	while (instack > -1)
	{
		stack = reduce(stack, instack);
		instack = keyinstack(*stack, next_tag);
	}
	return (*stack);
}
