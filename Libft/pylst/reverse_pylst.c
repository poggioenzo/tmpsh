/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   python_list.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: simrossi <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/10 10:32:13 by simrossi     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/15 18:39:06 by simrossi    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	reverse_pylst(t_pylst **pylst)
{
	t_pylst		*reverse_lst;
	t_pylst		*precedence;
	t_pylst		*next;

	if (!*pylst)
		return ;
	precedence = NULL;
	reverse_lst = *pylst;
	while (reverse_lst)
	{
		next = reverse_lst->next;
		reverse_lst->next = precedence;
		precedence = reverse_lst;
		reverse_lst = next;
	}
	*pylst = precedence;
}
