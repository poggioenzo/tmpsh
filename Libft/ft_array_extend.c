/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_array_extend.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: simrossi <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/07 08:24:11 by simrossi     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/07 09:02:09 by simrossi    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char		**ft_array_extend(char **array, char *string, int dup_str)
{
	int		len;
	int		index;
	char	**dup_array;

	len = ft_arraylen(array);
	if (!(dup_array = (char **)malloc(sizeof(char *) * (len + 2))))
		return (NULL);
	index = 0;
	while (array[index])
	{
		dup_array[index] = array[index];
		index++;
	}
	if (dup_str)
	{
		if (!(string = ft_strdup(string)))
		{
			free(dup_array);
			return (NULL);
		}
	}
	dup_array[index] = string;
	dup_array[index + 1] = NULL;
	free(array);
	return (dup_array);
}
