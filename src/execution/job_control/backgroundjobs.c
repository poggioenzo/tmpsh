#include "tmpsh.h"
#include "libft.h"
#include "job_control.h"

t_background_job		*g_jobs = NULL;

/*
** init_backgroundjobs:
**
** Allocate the global variable g_jobs and setup default value.
*/

void				init_backgroundjobs(void)
{
	g_jobs = (t_background_job *)ft_memalloc(sizeof(t_background_job));
	g_jobs->list_jobs = NULL;
	g_jobs->allow_background = true;
}

/*
** add_job:
**
** Add a new job (pipeline of command) into the list of background jobs.
*/

void				add_job(t_pylst *new_job)
{
	int		job_index;
	t_acb	*last_branch_job;

	last_branch_job = (t_acb *)index_pylst(new_job, -1)->value;
	new_job = pylst_shacpy(new_job);
	push_pylst(&g_jobs->list_jobs, new_job, NO_COPY_BUT_FREE, _pylst);
	job_index = len_pylst(g_jobs->list_jobs) - 1;
	ft_printf("[%d] %s\n", job_index, last_branch_job->pid);
}

/*
** is_running:
**
** Facility to check if a given job finised or if it still running.
**
** return : - true if the job is running.
**			- false if the job is over.
*/

enum e_waitstate	is_running(int index)
{
	t_pylst	*job;

	job = (t_pylst *)index_pylst(g_jobs->list_jobs, index)->value;
	return (analyse_job_status(job, WNOHANG));
}

/*
** remove_bg:
**
** @index : index to delete.
**
** Remove the job at the given index from the list of background processes.
*/

void				remove_bg(int index)
{
	t_pylst		*job;

	job = (t_pylst *)index_pylst(g_jobs->list_jobs, index)->value;
	remove_pylst(&g_jobs->list_jobs, job);
}

/*
** clear:
**
** Clean up the list of background processes.
*/

void				clear(void)
{
	free_pylst(&g_jobs->list_jobs, 0);
}
