/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_filejoin.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: simrossi <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/05 16:26:37 by simrossi     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/07 17:30:24 by simrossi    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char		*ft_filejoin(char **directory, char **filename, int free_dir,\
						int free_file)
{
	int		dir_len;
	char	*tmp_str;
	char	*tmp_dir;

	dir_len = ft_strlen(*directory);
	if ((*directory)[dir_len - 1] != '/')
	{
		tmp_str = "/";
		if ((tmp_dir = ft_fstrjoin(directory, &tmp_str, free_dir, 0)))
			return (ft_fstrjoin(&tmp_dir, filename, 1, free_file));
		if (free_dir)
			ft_strdel(directory);
		if (free_file)
			ft_strdel(filename);
		return (NULL);
	}
	return (ft_fstrjoin(directory, filename, free_dir, free_file));
}
