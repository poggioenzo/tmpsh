#include "libft.h"
#include "tmpsh.h"
#include "job_control.h"

/*
** is_job_id:
**
** Check if the given argument look like a job_id.
**
** !! Jobs id are not in POSIX format like expected in:
** https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/\
** V1_chap03.html#tag_03_204 !!
**
** Jobs id are only working with digit, with pattern like :
** "%[0-9]+"
*/

int				is_job_id(char *argument_name)
{
	return (argument_name[0] == '%' && digitstr(argument_name + 1));
}

/*
** bg_fg_map_argument:
**
** Go through each available argument, and map the fg or
** bg function to each job.
*/

static int		bg_fg_map_argument(char **argv, char *caller, \
		void (*function)(t_job *))
{
	int		job_id;
	t_job	*job;

	while (*argv)
	{
		if (is_job_id(*argv))
		{
			job_id = ft_atoi((*argv) + 1);
			if (!(job = get_job(job_id)))
			{
				ft_dprintf(2, "%s: No such job '%s'\n", caller, *argv);
				return (1);
			}
			function(job);
		}
		else
		{
			ft_dprintf(2, "%s: No such job '%s'\n", caller, *argv);
			return (1);
		}
		argv++;
	}
	return (0);
}

/*
** bg_fg_base:
**
** Common function for bg & fg. Those function have the same check
** for arguments, no options. They just behave differently
** for the given job. This difference is done by using
** a function pointer. (See bg et fg definition)
*/

int				bg_fg_base(char **argv, char *caller, \
		void (*function)(t_job *job))
{
	t_job	*default_job;

	if (ft_arraylen(argv) == 0)
	{
		if (len_pylst(g_jobs->list_jobs) == 0)
		{
			ft_dprintf(2, "%s: no current job\n", caller);
			return (1);
		}
		default_job = (t_job *)g_jobs->list_jobs->value;
		function(default_job);
		return (0);
	}
	return (bg_fg_map_argument(argv, caller, function));
}
