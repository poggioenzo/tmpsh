#include "libft.h"
#include "tmpsh.h"
#include "background_utils.h"
#include "argparser.h"
#include "job_control.h"

/*
** check_jobs_options:
**
** Check if options are valid and contain only -p or -l. Use the last given
** option, overide previous one.
** If an invalid options if found, display an error message.
*/

static int		check_jobs_options(char **argv, int *p_flag, int *l_flag)
{
	t_pylst		*options;
	char		*option_str;

	options = argparser(argv);
	while (iter_pylst(options, (void **)&option_str))
	{
		if (ft_strequ(option_str, "l"))
		{
			*l_flag = true;
			*p_flag = false;
		}
		else if (ft_strequ(option_str, "p"))
		{
			*l_flag = false;
			*p_flag = true;
		}
		else
		{
			ft_dprintf(2, "jobs: invalid option %s\n", option_str);
			return (free_pylst(&options, 1));
		}
	}
	return (free_pylst(&options, 0));
}

/*
** display_job:
**
** Print on stdout information about the given job.
** Format the output according to the expected options.
*/

static void	display_job(t_job *job, int p_flag, int l_flag)
{
	char	*status;
	t_acb	*first_branch;

	first_branch = job->branches->value;
	status = first_branch->running ? "Running" : "Stopped";
	if (p_flag)
		ft_printf("%d\n", job->pgid);
	else if (l_flag)
		ft_printf("[%d] - %d %s		%s\n", job->number, job->pgid, \
				status, job->command);
	else
		ft_printf("[%d] - %s	%s\n", job->number, status, job->command);
}

/*
** display_jobs_args:
**
** Go through each jobs arguments, and try to display all given job_id.
** Display appropriate error message if a wrong job id is given, and stop
** the display.
*/

static int		display_jobs_args(char **argv, int p_flag, int l_flag)
{
	int		job_id;
	t_job	*job;

	while (*argv)
	{
		if (is_job_id(*argv))
		{
			job_id = ft_atoi((*argv) + 1);
			job = get_job(job_id);
			if (!job)
			{
				ft_dprintf(2, "jobs: No such job : '%s'\n", *argv);
				return (1);
			}
			display_job(job, p_flag, l_flag);
		}
		else
		{
			ft_dprintf(2, "jobs: No such job: '%s'\n", *argv);
			return (1);
		}
		argv++;
	}
	return (0);
}

/*
** built_jobs:
**
** jobs - display status of jobs in the current session
**
** Synopsis: jobs [-l | -p] [job_id ...]
**
** Options:
** -l : Display job in long format, with job_id. 
**		Include the job number, pgid, state and command.
** -p : Only print pgid.
**
** Display information about all or each given job.
*/


int		built_jobs(char **argv, char **environ)
{
	int		p_flag;
	int		l_flag;
	t_pylst	*list_job;
	t_job	*job;

	UNUSED(environ);
	if (check_jobs_options(argv, &p_flag, &l_flag) == 1)
		return (1);
	if (ft_arraylen(argv) > 0)
		return (display_jobs_args(argv, p_flag, l_flag));
	list_job = g_jobs->list_jobs;
	while (iter_pylst(list_job, (void **)&job))
		display_job(job, p_flag, l_flag);
	return (0);
}
