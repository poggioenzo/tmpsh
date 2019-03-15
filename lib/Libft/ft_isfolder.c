/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_isfolder.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: simrossi <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/05 17:56:15 by simrossi     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/05 17:56:16 by simrossi    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <sys/stat.h>

int		ft_isfolder(char *filename)
{
	struct stat info;

	if (stat(filename, &info) == -1)
		return (-1);
	return (S_ISDIR(info.st_mode));
}
