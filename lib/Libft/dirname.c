/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   dirname.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: simrossi <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/05 15:20:18 by simrossi     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/05 16:04:55 by simrossi    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strrevchr(char *entry, char *stop, char c)
{
	while (entry >= stop)
	{
		if (*entry == c)
			return (entry);
		entry--;
	}
	return (NULL);
}

char		*dirname(char *filename)
{
	char	*slash;

	if (!(slash = ft_strrchr(filename, '/')))
		return (ft_strdup("."));
	if (*(slash + 1) == '\0')
	{
		*slash = '\0';
		if (!(slash = ft_strrevchr(slash - 1, filename, '/')))
			return (ft_strdup("."));
	}
	return (ft_strsub(filename, 0, slash - filename));
}
