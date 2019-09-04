/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   determine_bytes.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: simrossi <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/27 15:04:52 by simrossi     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/27 15:04:55 by simrossi    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"
#include "cd_canon.h"

/*
** canonicalize:
**
** From an absolute path, remove .. and . whenever it's possible.
** Edit the given path to be the absolute filename in his
** canonical form.
*/

void		canonicalize(char *path)
{
	char	*curr;

	remove_double_slash(path);
	curr = path;
	while (curr && *curr)
	{
		if (next_fileis(curr, "."))
			remove_dot(path, curr);
		else if (next_fileis(curr, ".."))
			reset_previous_dir(path, &curr);
		else
			curr = ft_strchr(curr + 1, '/');
	}
}
