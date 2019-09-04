/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   keyinstack_shiftreduce.c                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: epoggio <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/27 20:04:03 by epoggio      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/27 20:04:21 by epoggio     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "tmpsh.h"
#include "libft.h"
#include "tokenizer_utils.h"

/*
** revkeyinstack:
**
** Params:
** @stack: actual list of tags composing the stack.
**
** Return True if the pattern which is create in stack is syntaxic.
** Else return False.
** Tell us if we can append a new tag.
*/

t_bool			revkeyinstack(t_pylst *stack)
{
	size_t	len_stack;
	char	*key;
	t_bool	ret;
	t_pylst	*cpstack;

	ret = FALSE;
	len_stack = len_pylst(stack);
	while (len_stack-- && !ret)
	{
		cpstack = slice_pylst(stack, len_stack, len_pylst(stack));
		key = join_pylst(cpstack, " ");
		if (ops_begin_with(key, g_grammar->reverse_list))
		{
			ret = TRUE;
			free_pylst(&cpstack, ft_strdel_out(&key, 0));
			break ;
		}
		free_pylst(&cpstack, ft_strdel_out(&key, 0));
	}
	return (ret);
}

static	char	*get_ext_key(char *key, char *next_tag)
{
	char	*str;

	str = "";
	if (key)
	{
		str = ft_strjoin(key, " ");
		ft_strdel(&key);
	}
	return (ft_strjoin(str, next_tag));
}

/*
** keyinstack:
**
** Params:
** @stack: actual list of tags composing the stack.
** @next_tag: next tag which will may append to stack.
**
** Return the length of the reducable tags in the stack.
** If the next tag form a longer key -1 is return.
** If there is no pattern key finded -1 is return.
*/

int				keyinstack(t_pylst *stack, char *next_tag)
{
	char	*key;
	char	*ext_key;
	int		i;

	i = 0;
	while (stack)
	{
		key = join_pylst(stack, " ");
		ext_key = get_ext_key(ft_strdup(key), next_tag);
		if (search_value(g_grammar->reverse, key))
		{
			if (search_value(g_grammar->reverse, ext_key))
				break ;
			return (i);
		}
		ft_strdel_out(&ext_key, ft_strdel_out(&key, 0));
		i++;
		stack = stack->next;
	}
	return (-1);
}
