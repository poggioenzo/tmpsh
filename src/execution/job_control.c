#include "foreground.h"
#include "tmpsh.h"

t_background_job	*g_jobs;

void		waitpid_layer(int pid, int mode, int status[2])
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

enum e_waitstate	wait_subast(t_acb *job_branch, int mode)
{
	int		index;
	int		nbr_subast;
	t_ast	*subast;
	int		wait_res[2];
	int		state;

	nbr_subast = len_pylst(job_branch->subast);
	index = 0;
	while (index < nbr_subast)
	{
		subast = index_pylst(job_branch->subast, index);
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

enum e_waitstate	analyse_job_status(t_pylst *job_list, int mode)
{
	int		index;
	t_acb	*job;
	int		status[2];

	index = len_pylst(job_list) - 1;
	while (index >= 0)
	{
		job = index_pylst(job_list, index)->value;
		if (job->complete || job.pid == -1)
		{
			index -= 1;
			continue ;
		}
		wait_subast(job, mode);
		waitpid_layer(job->pid, mode, status);
		if (status[0] == 0 && status[1] == running)
			return (running);
		job->status = status[0];
		if (status[1] == running)
			return (running);
		job->complete = true;
		index--;
	}
	return (finish);
}

void	init_background_jobs(void)
{
	g_jobs->list_jobs = NULL;
	g_jobs->allow_background = true;
	return ;
}

void	add_job(t_pylst *new_job)
{
	int		job_index;
	t_acb	*last_branch_job;

	last_branch_job = (t_acb *)index_pylst(new_job, -1)->value;
	push_pylst(&g_jobs->list_jobs, pylst_shacpy(new_job));
	job_index = len_pylst(g_jobs->list_jobs) - 1;
	ft_printf("[%d] %s\n", job_index, last_branch_job->pid); 
}

pid_t		get_index_pid(int index)
{
	t_pylst		*job;

	job = index_pylst(g_jobs->list_jobs, index)->value;
	return (value->pid);
}


enum e_waitstate	is_running(int index)
{
	t_pylst	*job;

	job = (t_pylst *)index_pylst(g_jobs->list_jobs, index)->value;
	return (analyse_job_status(job, WNOHANG));
}

void	remove(int index)
{
	t_pylst		*job;

	job = (t_pyslt *)index_pylst(g_jobs->list_jobs, index)->value;
	remove_pylst(job);
}

void	clear(void)
{
	free_pylst(&g_jobs->list_jobs, 0);
}

void	relaunch(int index)
{
	t_pylst		*job;
	pid_t		new_tpgid;
	t_acb		*last_job_branch;

	if (is_running(index) == finish)
	{
        ft_printf("tmpsh: fg: job has terminated\n");
		remove(index);
		return ;
	}
	job = (t_pylst *)index_pylst(g_jobs->list_jobs, index)->value;
	new_tpgid = ((t_acb *)job->value)->pgid;
	set_foreground(new_pgid);
	kill(-new_tpgid, SIGCONT);
	if (analyse_job_status(job, WUNTRACED) == finish)
	{
		remove(index);
		last_job_branch = (t_acb *)index_pylst(job, -1)->value;
		ft_printf("[%d] + %d continued\n", index, last_branch_job->pid);
	}
	else
		ft_printf("[%d] + Suspended.\n", index);
	set_foreground(getpgrp());
	restore_tcattr();
}

void	wait_zombie(void)
{
	int		index;
	int		nbr_job;
	int		index_job;
	t_pylst	*job;
	t_acb	*last_branch;

	index = 0;
	index_job = 0;
	nbr_job = len_pylst(g_jobs->list_jobs);
	while (index < nbr_job)
	{
		if (is_running(index) == finish)
		{
			job = (t_pylst *)index_pylst(g_jobs->list_jobs, index)->value;
			remove(index);
			index--;
			last_branch = (t_acb *)index_pylst(job, -1)->value;
			ft_printf("[%d] + Done %s\n", index_job, last_branch->command);
		}
		index++;
		index_job++;
	}
}
