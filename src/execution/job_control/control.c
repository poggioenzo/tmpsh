#include <signal.h>
#include "tmpsh.h"
#include "libft.h"
#include "foreground.h"
#include "job_control.h"

/*
** waitpid_layer:
**
** @pid: pid to wait.
** @mode: waitpid options argument.
** @status: Array to store status and state.
**
** Layer for waitpid, who will analyse the result depending
** of the program death. Return the good status value,
** and the state, if it's finish or running.
*/

static void				waitpid_layer(int pid, int mode, int status[2])
{
	int		return_status;

	pid = waitpid(pid, &return_status, mode);
	if (pid == 0)
	{
		status[0] = 0;
		status[1] = running;
	}
	else if (WIFSTOPPED(return_status))
	{
		status[0] = WSTOPSIG(return_status) + 128;
		status[1] = running;
	}
	else if (WIFSIGNALED(return_status))
	{
		status[0] = WTERMSIG(return_status) + 128;
		status[1] = finish;
	}
	else if (WIFEXITED(return_status))
	{
		status[0] = WEXITSTATUS(return_status);
		status[1] = finish;
	}
}

/*
** wait_subast:
**
** @job_branch: Branch where subast have to be waited.
** @mode: waiptid options argument.
**
** Inside a single branch, go to wait subast who need to be waited.
** Save his state in the subast->complete value.
**
** return : - the enum running if any suabst is not complete.
**			- finish if all subast are complete.
*/

static enum e_waitstate	wait_subast(t_acb *job_branch, int mode)
{
	int		index;
	int		nbr_subast;
	t_ast	*subast;
	int		wait_res[2];

	nbr_subast = len_pylst(job_branch->subast);
	index = 0;
	while (index < nbr_subast)
	{
		subast = index_pylst(job_branch->subast, index)->value;
		if ((ft_strequ(subast->type, "CMDSUBST2") || \
				ft_strequ(subast->type, "CMDSUBST3")) &&
				subast->complete == false)
		{
			waitpid_layer(subast->pid, mode, wait_res);
			if (wait_res[1] == running)
				return (running);
			else if (wait_res[1] == finish)
				subast->complete = true;
		}
		index++;
	}
	return (finish);
}

/*
** analyse_job_status:
**
** @job: Pipeline of commands, or single one branch, to analyse.
** @mode: waitpid options arguments.
**
** Go through each branch, and try to wait each available process.
** It could be the branch herself, but also any subast processes.
** Will care about wait each child process only a single time, to avoid zombie.
*/

enum e_waitstate		analyse_job_status(t_pylst *job, int mode)
{
	int		index;
	t_acb	*branch;
	int		status[2];

	index = len_pylst(job) - 1;
	while (index >= 0)
	{
		branch = (t_acb *)index_pylst(job, index)->value;
		if (branch->complete || branch->pid == -1)
		{
			index--;
			continue ;
		}
		wait_subast(branch, mode);
		waitpid_layer(branch->pid, mode, status);
		if (status[0] == 0 && status[1] == running)
			return (running);
		branch->status = status[0];
		if (status[1] == running)
			return (running);
		branch->complete = true;
		index--;
	}
	return (finish);
}

/*
** relaunch:
**
** @index: Index of the job to relaunch.
**
** Check if the given job number can be relaunched and pushed
** in foreground.
** Will wait the given job and choose to keep or remove it from
** the g_jobs->list_jobs if it's finish.
*/

void					relaunch(int index)
{
	t_pylst		*job;
	pid_t		new_tpgid;
	t_acb		*last_job_branch;

	if (is_running(index) == finish)
	{
		ft_printf("tmpsh: fg: job has terminated\n");
		remove_bg(index);
		return ;
	}
	job = (t_pylst *)index_pylst(g_jobs->list_jobs, index)->value;
	new_tpgid = ((t_acb *)job->value)->pgid;
	set_foreground(new_tpgid);
	kill(-new_tpgid, SIGCONT);
	if (analyse_job_status(job, WUNTRACED) == finish)
	{
		last_job_branch = (t_acb *)index_pylst(job, -1)->value;
		ft_printf("[%d] + %d continued\n", index, last_job_branch->pid);
		remove_bg(index);
	}
	else
		ft_printf("[%d] + Suspended.\n", index);
	set_foreground(getpgrp());
	restore_tcattr();
}

/*
** wait_zombie:
**
** Called before giving back the prompt to the user.
** Check if some jobs are done and remove them from the current joblist.
*/

void					wait_zombie(void)
{
	int		index;
	int		nbr_job;
	int		index_job;
	t_pylst	*job;
	t_acb	*last_branch;

	index = 0;
	index_job = 0;
	nbr_job = len_pylst(g_jobs->list_jobs);
	while (index_job < nbr_job)
	{
		if (is_running(index) == finish)
		{
			job = (t_pylst *)index_pylst(g_jobs->list_jobs, index)->value;
			last_branch = (t_acb *)index_pylst(job, -1)->value;
			ft_printf("[%d] + Done %s\n", index_job, last_branch->command);
			remove_bg(index);
			index--;
		}
		index++;
		index_job++;
	}
}
