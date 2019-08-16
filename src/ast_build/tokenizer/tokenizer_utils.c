/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tokenizer_utils.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: epoggio <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/16 10:04:32 by epoggio      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/16 10:06:53 by epoggio     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "tmpsh.h"
#include "libft.h"

/*
** ops_begin_with:
**
** @pattern: operator tested pattern.
** @leaf_op: list of atomic operator of the grammar.
**
** Return True if the lengthed begin of the given pattern is identical to
** the lengthed begin of one operator in leaf_op.
*/

int	ops_begin_with(char *pattern, t_pylst *leaf_op)
{
	int		i;
	char	*leaf;
	t_bool	ret;

	ret = FALSE;
	i = ft_strlen(pattern);
	while (pylst_iter(leaf_op, (void **)&leaf))
		if (ft_strnequ(pattern, leaf, i))
		{
			ret = TRUE;
			leaf_op->iter_item = NULL;
			break ;
		}
	return (ret);
}
