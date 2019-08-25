#include "libft.h"
#include "tmpsh.h"
#include <signal.h>
#include "background_utils.h"

static void		fg_action(t_job *job)
{
	relaunch(job->number);
}

int		fg(char **argv, char **environ)
{
	return (bg_fg_base(argv, "fg", fg_action));
}

static void		bg_action(t_job *job)
{
	t_acb	*first_branch;

	first_branch = (t_acb *)job->branches->values;
	if (first_branch->running == false)
	{
		first_branch->running = true;
		kill(-job->pgid, SIGCONT);
		ft_printf("[%s] %s\n", job->number, job->command);
	}
}

int		bg(char **argv, char **environ)
{
	return (bg_fg_base(argv, "bg", bg_action));
}
