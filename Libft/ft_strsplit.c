/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strsplit.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: simrossi <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/30 09:05:06 by simrossi     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/14 10:08:43 by simrossi    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

/*
** ft_strplit :
**
** Cut a given string with the specified charset
*/

char			**ft_strsplit(const char *str, const char *charset)
{
	char	**tab;
	int		tab_index;
	int		nb_elem;
	char	*delim;

	nb_elem = ft_count(str, charset);
	tab = (char **)ft_memalloc(sizeof(char *) * (nb_elem + 1));
	tab_index = 0;
	while (nb_elem)
	{
		if (ft_incharset(*str, charset))
			str++;
		else
		{
			delim = ft_strpbrk(str, charset);
			tab[tab_index++] = delim ? ft_strsub(str, 0, delim - str) :\
						ft_strdup(str);
			nb_elem--;
			str = delim + 1;
		}
	}
	tab[tab_index] = NULL;
	return (tab);
}
