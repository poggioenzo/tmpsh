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
#include "job_control.h"

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

t_job				*get_job(int job_id)
{
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
	t_job	*new_job;

	new_job = job_init(job_branches);
	push_pylst(&g_jobs->list_jobs, new_job, NO_COPY_BUT_FREE, _job);
	sort_pylst(&g_jobs->list_jobs, sort_jobs);
	ft_printf("[%d] %d\n", new_job->number, new_job->pgid);
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
** wait_zombie:
**
** Called before giving back the prompt to the user.
** Check if some jobs are done and remove them from the current joblist.
*/

void					wait_zombie(void)
{
	t_pylst		*list_jobs;
	t_pylst		*next_list_jobs;
	t_job		*job;

	list_jobs = g_jobs->list_jobs;
	while (list_jobs)
	{
		job = (t_job *)list_jobs->value;
		next_list_jobs = list_jobs->next;
		if (is_running(job->number) == finish)
		{
			ft_printf("[%d] + Done %s\n", job->number, job->command);
			remove_bg(job->number);
		}
		list_jobs = next_list_jobs;
	}
}
