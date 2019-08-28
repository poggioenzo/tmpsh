#include "libft.h"
#include "tmpsh.h"
#include <signal.h>
#include "background_utils.h"
#include "control.h"

/*
** fg_action:
**
** Pointer to send to bg_fg_base. Fg just relaunch in background
** any given job.
*/

static void		fg_action(t_job *job)
{
	relaunch(job->number);
}

/*
** built_fg:
**
** fg - Run job in foreground
**
** Synopsis : fg [job_id ...]
*/

int				built_fg(char **argv, NOT_USE(char **environ))
{
	return (bg_fg_base(argv, "fg", fg_action));
}

/*
** bg_action:
**
** Pointer to send to bg_fg_base. Bg check if the given
** job is running, and if it's actually stopped, relaunch it.
** Keep it in background.
*/

static void		bg_action(t_job *job)
{
	t_acb	*first_branch;

	first_branch = (t_acb *)job->branches->value;
	if (first_branch->running == false)
	{
		first_branch->running = true;
		kill(-job->pgid, SIGCONT);
		ft_printf("[%s] %s\n", job->number, job->command);
	}
}

/*
** built_bg:
**
** bg - Run job in the background.
**
** Synopsis: bg [job_id ...]
**
** Relaunch all or given job who are stopped in the background.
*/

int				built_bg(char **argv, NOT_USE(char **environ))
{
	return (bg_fg_base(argv, "bg", bg_action));
}
