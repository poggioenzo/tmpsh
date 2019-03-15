/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   basename.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: simrossi <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/05 15:21:00 by simrossi     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/05 15:24:35 by simrossi    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char		*basename(char *filename)
{
	char	*slash;

	if (!(slash = ft_strrchr(filename, '/')))
		return (ft_strdup(filename));
	return (ft_strsub(slash + 1, 0, ft_strlen(slash + 1)));
}
