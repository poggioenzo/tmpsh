/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   determine_bytes.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: simrossi <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/27 15:04:52 by simrossi     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/25 13:05:29 by simrossi    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "tmpsh.h"
#include "fd_management.h"

/*
** replace_fd:
**
** @expected_fd: Fd to use in replacement.
** @old_fd: Fd to replace.
**
** Replace properly a fd using dup2.
*/

int		replace_fd(int expected_fd, int old_fd, t_bool close_expected_fd)
{
	int		res;

	res = dup2(expected_fd, old_fd);
	if (close_expected_fd)
		close(expected_fd);
	return (res);
}

/*
** replace_std_fd:
**
** @stdin: Fd to use as stdin.
** @stdout: Fd to use as stdout.
**
** Check if stdin or stdout have to be change, and perform this
** change if necessary.
*/

void	replace_std_fd(int stdin, int stdout)
{
	if (stdin != -1)
		replace_fd(stdin, STDIN_FILENO, true);
	if (stdout != -1)
		replace_fd(stdout, STDOUT_FILENO, true);
}

/*
** setup_pipe_fd:
**
** @pipes_fd: array to store new pipe fds.
**
** Perfom a pipe and push them in a bigger fd (starting from shell_range)
** to limit conflict with user program.
**
** return : - 0 if pipe success
**			- -1 if an error occur.
*/

int		setup_pipe_fd(int pipes_fd[2])
{
	int		shell_range;
	int		sys_pipes[2];
	int		status;

	shell_range = 63;
	if ((status = pipe(sys_pipes)) == -1)
		return (status);
	pipes_fd[0] = fcntl(sys_pipes[0], F_DUPFD, shell_range);
	pipes_fd[1] = fcntl(sys_pipes[1], F_DUPFD, shell_range);
	close(sys_pipes[0]);
	close(sys_pipes[1]);
	return (0);
}

/*
** save_std_fd:
**
** @mode : Call the function in save to restore mode.
**
** In the save mode, save current stdin, stdout or stderr
** to be replace freely. In restore mode, reset old stdin/out/err.
*/

void	save_std_fd(enum e_save_fd mode)
{
	static int	std_fds[3];

	if (mode == save)
	{
		std_fds[0] = fcntl(STDIN_FILENO, F_DUPFD_CLOEXEC, 100);
		std_fds[1] = fcntl(STDOUT_FILENO, F_DUPFD_CLOEXEC, 100);
		std_fds[2] = fcntl(STDERR_FILENO, F_DUPFD_CLOEXEC, 100);
	}
	else if (mode == restore)
	{
		replace_fd(std_fds[0], STDIN_FILENO, true);
		replace_fd(std_fds[1], STDOUT_FILENO, true);
		replace_fd(std_fds[2], STDERR_FILENO, true);
	}
}
