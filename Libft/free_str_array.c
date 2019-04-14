/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   free_str_array.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: epoggio <epoggio@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/15 16:46:16 by epoggio      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/14 09:03:14 by simrossi    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

int			free_str_array(char ***str, int status)
{
	int index;

	index = 0;
	if (!*str)
		return (status);
	while ((*str)[index])
		ft_strdel(&(*str)[index++]);
	FREE(*str);
	*str = NULL;
	return (status);
}
