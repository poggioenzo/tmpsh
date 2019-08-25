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
** get_job:
**
** @job_id: Searched job identifier.
**
** Go through the entire list of background job and return the
** expected job.
**
** return: - NULL if job_id is not availble.
**		   - Job with a job->number corresponding to job_id
*/

t_job			*get_job(int job_id)
{
	int		nbr_jobs;
	int		index;
	t_pylst	*list_jobs;
	t_job	*job;

	list_jobs = g_jobs->list_jobs;
	while (list_jobs)
	{
		job = list_jobs->value;
		if (job->number == job_id)
			return (job);
		list_jobs = list_jobs->next;
	}
	return (NULL);
}

/*
** sort_jobs:
**
** Function to sort pylst in add_job.
*/

static int			sort_jobs(t_pylst *job_a, t_pylst *job_b)
{
	t_job		*first_job;
	t_job		*second_job;

	first_job = (t_job *)job_a->value;
	second_job = (t_job *)job_b->value;
	return (first_job->number - second_job->number);
}

/*
** add_job:
**
** Add a new job (pipeline of command) into the list of background jobs.
*/

void				add_job(t_pylst **job_branches)
{
	int		job_index;
	t_acb	*last_branch_job;
	t_job	*new_job;

	new_job = job_init(new_job);
	push_pylst(&g_jobs->list_jobs, new_job, NO_COPY_BUT_FREE, _ptr); //Use _job as type
	sort_pylst(&g_jobs->list_jobs, sort_jobs);
	ft_printf("[%d] %s\n", new_job->number, new_job->pgid);
}

/*
** is_running:
**
** Facility to check if a given job finised or if it still running.
**
** return : - true if the job is running.
**			- false if the job is over.
*/

enum e_waitstate	is_running(int job_id)
{
	t_job	*job;

	job = get_job(job_id);
	return (analyse_job_status(job->branches, WNOHANG | WUNTRACED));
}

/*
** remove_bg:
**
** @index : index to delete.
**
** Remove the job at the given index from the list of background processes.
*/

void				remove_bg(int job_id)
{
	t_job	*job;

	job = get_job(job_id);
	if (job)
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
