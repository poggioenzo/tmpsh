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
** del_portion_pylst:
**
** Delete in the given list element with range [from:to[
*/

void	del_portion_pylst(t_pylst **pylst, int from, int to)
{
	t_pylst	*start;
	t_pylst	*end;
	t_pylst	*start_precedence;

	if (from == to)
		return ;
	start_precedence = precedence_pylst(*pylst, from);
	start = start_precedence ? start_precedence->next : *pylst;
	end = precedence_pylst(*pylst, to);
	if (!start_precedence && !end)
		return ;
	if (start_precedence)
		start_precedence->next = end->next;
	else
		*pylst = end->next;
	end->next = NULL;
	free_pylst(&start, 0);
}
