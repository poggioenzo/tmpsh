#include "libft.h"
#include "tmpsh.h"

int				is_job_id(char *argument_name)
{
	return (argument_name[0] == '%' && digitstr(argument_name + 1));
}

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
			job = get_job(job_id);
			if (!job)
			{
				ft_dprintf("%s: No such job '%s'\n", caller, *argv);
				return (1);
			}
			function(job);
			argv++;
		}
	}
	return (0);
}

int			bg_fg_base(char **argv, char *caller, \
		void (*function)(t_job *job))
{
	t_job	*default_job;
	int		job_id;
	t_job	*job;

	if (ft_arraylen(argv) == 0)
	{
		if (len_pylst(g_jobs->list_jobs) == 0)
		{
			ft_dprintf(2, "%s: no current job\n", caller);
			return (1);
		}
		default_job = (t_job *)g_jobs->list_jobs->value;
		function(default_job);
		return ;
	}
	bg_fg_map_argument(argv, caller, function);
}

