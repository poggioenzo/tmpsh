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

static int		create_job_index(void)
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
** concat_job_command:
**
** Use each branch who compose a job and concat their command
** attribute in a single one attribute.
** Add delimiters manually between each command.
*/

static char		*concat_job_command(t_pylst *job_branches)
{
	char	*command;
	char	*tmp;
	t_acb	*branch;

	command = ft_strnew(0);
	while (job_branches)
	{
		branch = job_branches->value;
		command = ft_fstrjoin(&command, &branch->command, true, false);
		if (!ft_strequ(branch->tag_end, ""))
		{
			tmp = " ";
			command = ft_fstrjoin(&command, &tmp, true, false);
			tmp = ((t_pylst *)search_value(g_grammar->grammar, \
						branch->tag_end))->value;
			command = ft_fstrjoin(&command, &tmp, true, false);
			if (job_branches->next)
			{
				tmp = " ";
				command = ft_fstrjoin(&command, &tmp, true, false);
			}
		}
		job_branches = job_branches->next;
	}
	return (command);
}

/*
** job_init:
**
** Allocate a single t_job and setup his attributes.
*/

t_job			*job_init(t_pylst **job_branches)
{
	t_job	*new_job;
	t_acb	*last_branch;

	new_job = (t_job *)ft_memalloc(sizeof(t_job));
	new_job->branches = *job_branches;
	*job_branches = NULL;
	new_job->number = create_job_index();
	last_branch = vindex_pylst(new_job->branches, -1);
	new_job->pgid = last_branch->pgid;
	new_job->command = concat_job_command(new_job->branches);
	return (new_job);
}
