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

#include "tmpsh.h"
#include "libft.h"
#include "foreground.h"

/*
** fork_prepare:
**
** @pgid : process group id of the new fork.
** @background: Boolean to see if background is expected.
**
** Fork layer. Set up the forked child in foreground if
** expected.
*/

int		fork_prepare(int pgid, t_bool background)
{
	pid_t pid;

	pid = fork();
	if (g_jobs->allow_background == true)
	{
		setpgid(pid, pgid);
		if (background == false)
			set_foreground(getpgid(pid));
	}
	return (pid);
}
