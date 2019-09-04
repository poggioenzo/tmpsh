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
#include "tmpsh.h"
#include <fcntl.h>

/*
** built_exit:
**
** exit - quit the current shell process
**
** Synopsis : exit [n]
*/

int		built_exit(char **args, NOT_USE(char **env))
{
	int		argc;
	int		value;
	int		term;

	argc = ft_arraylen(args);
	if (argc >= 2)
	{
		ft_dprintf(2, "exit: too many arguments\n");
		return (1);
	}
	else if (argc == 1)
		value = ft_atoi(args[0]);
	else
		value = 0;
	term = open("/dev/tty", O_WRONLY);
	ft_dprintf(term, "%s", g_caps->reset_cursor);
	close(term);
	exit(value);
}
