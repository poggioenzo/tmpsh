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
** iter_pylst:
**
** @pylst: chained list head selected to iterate.
** @value: void * pointer to get value one by one in the list.
**
** Used in a while loop to iterate over each element of a pylst.
** Make a for loop inspired from python.
** ! No change on the pylst should be done during the iteration !
** ! The list have to be iterate entirely (or reset iter_item) !
**
** return : - 1 if a next element if found.
**			- 0 if pylst is NULL, or if the entire list is parsed.
*/

int		iter_pylst(t_pylst *pylst, void **value)
{
	if (!pylst)
		return (0);
	if (!pylst->iter_item)
		pylst->iter_item = pylst;
	else
		pylst->iter_item = pylst->iter_item->next;
	if (pylst->iter_item)
	{
		*value = pylst->iter_item->value;
		return (1);
	}
	return (0);
}
