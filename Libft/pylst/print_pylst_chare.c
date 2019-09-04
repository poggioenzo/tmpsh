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
** print_pylst_chare:
**
** Arguments, in order :
** @pylst: choosen list.
**
** Print a python'style list of string.
** ! Work only if pylst values are char * !
*/

void	print_pylst_chare(t_pylst *pylst)
{
	if (!(pylst))
	{
		ft_printf("Empty list.\n");
		return ;
	}
	ft_printf(str_chare_pylst(pylst));
}
