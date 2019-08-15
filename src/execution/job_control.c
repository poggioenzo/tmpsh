#include "foreground.h"
#include "tmpsh.h"

t_background_job	*g_jobs;

static t_pylst		*prepare_waitpid_return(int status, enum e_waitstate state)
{
	t_pylst		*return_wait;

	return_wait = NULL;
	push_pylst(&return_wait, &status, 0, _ptr);
	push_pylst(&return_wait, &state, 0, _ptr);
}

t_pylst		*waitpid_layer(int pid, int mode)
{
	int		status;

	pid = waitpid(pid, &status, mode);
	if (pid == 0)
		return (prepare_waitpid_return(0, running));
	if (WIFSTOPPED(status))
	{
		status = WSTOPSIG(status) + 128;
		return (prepare_waitpid_return(status, running));
	}
	else if (WIFSIGNALED(status))
	{
		status = WTERMSIG(status) + 128;
		return (prepare_waitpid_return(status, finish));
	}
	else if (WIFEXITED(status))
	{
		status = WEXITSTATUS(status);
		return (prepare_waitpid_return(status, finish));
	}
	return (NULL);
}

enum e_waitstate	wait_subast(t_acb *job_branch, int mode)
{
	int		index;
	int		nbr_subast;
	t_ast	*subast;

	nbr_subast = len_pylst(job_branch->subast);
	index = 0;
	while (index < nbr_subast)
	{
	
	}
}

void	init_background_jobs(void)
{
	return ;
}


