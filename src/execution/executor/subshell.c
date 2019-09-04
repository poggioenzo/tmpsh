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
#include "forker.h"
#include "setup_redirection.h"
#include "job_control.h"
#include "fd_management.h"
#include "run_ast.h"
#include "reset_signals.h"
#undef stdin
#undef stdout

pid_t	run_subshell(t_acb *branch, t_ast *subast)
{
	pid_t	pid;

	pid = fork_prepare(branch->pgid, branch->background);
	if (pid == 0)
	{
		if (setup_redirection(branch) == false)
			exit(1);
		reset_signals();
		clear();
		g_jobs->allow_background = false;
		replace_std_fd(branch->stdin, branch->stdout);
		run_ast(subast);
		exit(g_last_status);
	}
	if (branch->stdin >= 0)
		close(branch->stdin);
	if (branch->stdout >= 0)
		close(branch->stdout);
	return (pid);
}
