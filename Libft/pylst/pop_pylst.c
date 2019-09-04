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
** pop_pylst:
**
** Return a value and delete it from the pylst.
*/

void		*pop_pylst(t_pylst **pylst, int index)
{
	t_pylst		*pop_node;
	int			gold_index;
	void		*pop_value;

	gold_index = convert_index(*pylst, index);
	pop_node = index_pylst(*pylst, gold_index);
	pop_value = pop_node->value;
	pop_node->size = 0;
	del_portion_pylst(pylst, gold_index, gold_index + 1);
	return (pop_value);
}
