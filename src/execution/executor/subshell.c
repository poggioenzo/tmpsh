#include "tmpsh.h"
#include "libft.h"
#include "forker.h"
#include "setup_redirection.h"
#include "job_control.h"
#include "fd_management.h"
#include "run_ast.h"
#undef stdin
#undef stdout
//run_ast header

pid_t	run_subshell(t_acb *branch, t_ast *subast)
{
	pid_t	pid;

	pid = fork_prepare(branch->pgid, branch->background);
	if (pid == 0)
	{
		setup_redirection(branch);
		//reset_signals();
		clear();
		g_jobs->allow_background = false;
		replace_std_fd(branch->stdin, branch->stdout);
		run_ast(subast);
		exit(g_last_status);
	}
	else
	{
		if (branch->stdin >= 0)
			close(branch->stdin);
		if (branch->stdout >= 0)
			close(branch->stdout);
		return (pid);
	}
}

