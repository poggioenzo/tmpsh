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
** remove_pylst:
**
** @pylst: list where the element have to be removed.
** @value: Value tu remove.
**
** Delete a single value in the current list.
*/

void		remove_pylst(t_pylst **pylst, void *value)
{
	t_pylst		*prev;
	t_pylst		*curr;

	prev = NULL;
	curr = *pylst;
	while (curr && curr->value != value)
	{
		prev = curr;
		curr = curr->next;
	}
	if (!curr)
		return ;
	if (!prev)
		*pylst = (*pylst)->next;
	else
		prev->next = curr->next;
	free_pylst_node(&curr, 0);
}
