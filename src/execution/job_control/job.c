#include "tmpsh.h"
#include "libft.h"

/*
** create_job_index:
**
** Determine the new index to give to a single job according
** to the current job list.
** Retrieve the first available index who have no job associated
** to him.
*/

static int			create_job_index(void)
{
	int		index;
	int		nbr_jobs;
	t_job	*job;
	t_pylst	*job_list;

	job_list = g_jobs->list_jobs;
	nbr_jobs = len_pylst(job_list);
	index = 0;
	while (index < nbr_jobs)
	{
		job = (t_job *)job_list->value;
		if (job->number > index)
			return (index);
		index++;
		job_list = job_list->next;
	}
	return (index);
}

/*
** job_init:
**
** Allocate a single t_job and setup his attributes.
*/

t_job		*job_init(t_pylst **job_branches)
{
	t_job	*new_job;
	t_acb	*last_branch;

	new_job = (t_job *)ft_memalloc(sizeof(t_job));
	new_job->branches = *job_branches;
	*job_branches = NULL;// Check how job have top be copied !!!
	new_job->number = create_job_index();
	last_branch = vindex_pylst(*job_branches, -1);
	new_job->pgid = last_branch->pgid;
	new_job->command = last_branch->command;//Need to get good command
	return (new_job);
}
