/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_array_remove.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: simrossi <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/05 18:08:24 by simrossi     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/14 09:04:21 by simrossi    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"
#include <fcntl.h>

/*
** ft_array_remove:
**
** Remove a single string in the given array. Free the string if asked.
*/

void		ft_array_remove(char **array, char *string, int free_str)
{
	int index;

	index = 0;
	while (array[index] && ft_strequ(array[index], string) == 0)
		index++;
	if (!array[index])
		return ;
	if (free_str)
		FREE(string);
	while (array[index])
	{
		array[index] = array[index + 1];
		index++;
	}
}
