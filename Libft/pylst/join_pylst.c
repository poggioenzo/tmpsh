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
** join_pylst:
**
** Concat each element of the pylst according to the given char.
** WARNING : Must be use with char *element.
*/

char	*join_pylst(t_pylst *pylst, char *substr)
{
	char	*concat_str;
	char	*py_str;

	concat_str = ft_strnew(0);
	while (pylst)
	{
		py_str = pylst->value;
		if (py_str)
			concat_str = ft_fstrjoin(&concat_str, &py_str, TRUE, FALSE);
		pylst = pylst->next;
		if (py_str && pylst)
			concat_str = ft_fstrjoin(&concat_str, &substr, TRUE, FALSE);
	}
	return (concat_str);
}
