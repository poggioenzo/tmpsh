/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strmap.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: simrossi <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/12 10:57:09 by simrossi     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/14 10:06:31 by simrossi    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *str, char (*fct)(char))
{
	char	*map_str;
	int		index;

	map_str = (char *)ft_memalloc(sizeof(char) * (ft_strlen(str) + 1));
	index = 0;
	while (*str)
		map_str[index++] = fct(*str++);
	map_str[index] = '\0';
	return (map_str);
}
