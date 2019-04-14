/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   create_tab.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: epoggio <epoggio@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/24 17:38:29 by epoggio      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/14 09:58:10 by simrossi    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

/*
** create_tab:
**
** Allocate a char ** from a given size. Set all index to NULL.
*/

#include "libft.h"

char	**create_tab(int size)
{
	int		i;
	char	**tab;

	if (!(tab = (char **)MALLOC(sizeof(char *) * (size + 1))))
		return (NULL);
	i = 0;
	while (i <= size)
		tab[i++] = NULL;
	return (tab);
}
