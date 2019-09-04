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
** extend_pylst:
**
** Add a pylst to an other pylst.
*/

void	extend_pylst(t_pylst **start, t_pylst *end, int deep_cpy)
{
	t_pylst		*end_cpy;

	if (!*start && !end)
		return ;
	end_cpy = deep_cpy ? pylst_deepcpy(end) : pylst_shacpy(end);
	while (*start && (*start)->next)
		start = &(*start)->next;
	if (!*start)
		*start = end_cpy;
	else
		(*start)->next = end_cpy;
}
