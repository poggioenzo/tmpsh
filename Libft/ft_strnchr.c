/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strnchr.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: simrossi <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/05 15:31:23 by simrossi     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/05 16:05:34 by simrossi    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnchr(char *str, char c, int len)
{
	if (c == 0)
		return (str + ft_strlen(str));
	while (len > 0 && *str)
	{
		if (*str == c)
			return (str);
		len--;
		str++;
	}
	return (NULL);
}
