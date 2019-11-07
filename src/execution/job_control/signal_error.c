/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   signal_error.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: simrossi <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/07 15:52:18 by simrossi     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/07 16:07:03 by simrossi    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "tmpsh.h"

char		*g_signals[] = {
	"Hangup",
	NULL,
	"Quit",
	"Illegal instruction",
	"Trace/BPT trap",
	"Abort trap",
	"EMT trap",
	"Floating point exception",
	"Killed",
	"Bus error",
	"Segmentation fault",
	"Bad system call",
	NULL,
	"Alarm clock",
	"Terminated",
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	"Cputime limit exceeded",
	NULL,
	"Virtual timer expired",
	"Profiling timer expired",
	NULL,
	NULL,
	"User defined signal 1",
	"User defined signal 2",
};

void	display_signal_error(int signum)
{
	char	*str;

	if (signum <= 30)
	{
		str = g_signals[signum - 1];
		if (str)
			ft_dprintf(2, "%s: %d\n", str, signum);
	}
}
