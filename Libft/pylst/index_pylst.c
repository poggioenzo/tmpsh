/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   determine_bytes.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: simrossi <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/27 15:04:52 by simrossi     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/27 15:04:55 by simrossi    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

/*
** index_pylst:
**
** Return the t_pylst element of the given index.
** Allow performing negativ research.
** WARNING : Will segfault if wrong index (IndexError)
*/

t_pylst		*index_pylst(t_pylst *pylst, int index)
{
	index = convert_index(pylst, index);
	while (pylst && index--)
		pylst = pylst->next;
	return (pylst);
}

/*
** vindex_pylst:
**
** Like index_pylst, but return the t_pylst->value element.
*/

void		*vindex_pylst(t_pylst *pylst, int index)
{
	t_pylst		*expect_node;

	expect_node = index_pylst(pylst, index);
	return (expect_node ? expect_node->value : NULL);
}
