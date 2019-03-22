/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strcount.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: simrossi <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/19 15:37:32 by simrossi     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/19 15:40:53 by simrossi    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

/*
** ft_strcount:
**
** Count the number of occurence of c in the string str.
*/

size_t		ft_strcount(const char *str, char c)
{
	int		count;

	count = 0;
	while (*str)
		count += *str++ == c ? 1 : 0;
	return (count);
}
