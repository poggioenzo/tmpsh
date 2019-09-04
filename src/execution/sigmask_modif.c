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

#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#ifndef NULL
# define NULL (void *) 0
#endif

/*
** change_sigmask:
**
** @signum : Signal to impact.
** @action : behavior on sigmask (SIG_BLOCK || SIG_UNBLOCK)
**
** Manipulate the sigmask of the calling process,
** acting like specified by action on signum.
*/

int		change_sigmask(int signum, int action)
{
	sigset_t	set;

	sigemptyset(&set);
	sigaddset(&set, signum);
	return (sigprocmask(action, &set, NULL));
}
