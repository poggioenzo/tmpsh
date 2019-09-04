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
** clear:
**
** Clean up the list of background processes.
*/

void				clear(void)
{
	free_pylst(&g_jobs->list_jobs, 0);
}
