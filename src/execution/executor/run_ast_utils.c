#include "tmpsh.h"
#include "libft.h"
#include "fd_management.h"
#undef stdin
#undef stdout

/*
** setup_branch_pipe:
**
** Whenever a branch is pipe, make a system call to create a pipe,
** and assign them to stdin/stdout of related branches.
*/

void		setup_branch_pipe(t_acb *branch, t_acb *next_branch)
{
	int		new_pipe[2];

	setup_pipe_fd(new_pipe);
	next_branch->stdin = new_pipe[0];
	branch->stdout = new_pipe[1];
}

/*
** close_subast_pipe:
**
** Go through each subast of the the branch, and for each CMDSUBST,
** close the AST.link_fd attribute, who his the fd to read/write
** with the CMDSUBST.
*/

void		close_subast_pipe(t_acb *branch)
{
	t_ast	*subast;

	while (iter_pylst(branch->subast, (void **)&subast))
	{
		if (ft_start_with(subast->type, "CMDSUBST"))
			close(subast->link_fd);
		else if (ft_strequ(subast->type, "DQUOTES"))
			close_subast_pipe(subast->list_branch->value);
	}
}

/*
** check_background:
**
** Check if the branch have to be run in background or
** in foreground.
** If it's pipe, check the last element of the pipeline to
** see the behavior to apply.
*/

t_bool		check_background(t_acb *branch, t_pylst *list_branch)
{
	t_acb	*next_branch;

	if (branch->background == true)
		return (true);
	else if (ft_strequ(branch->tag_end, "BACKGROUND_JOBS"))
	{
		branch->background = true;
		return (true);
	}
	else if (g_jobs->allow_background == false)
		return (false);
	else if (ft_strequ(branch->tag_end, "PIPE"))
	{
		next_branch = vindex_pylst(list_branch, 0);
		next_branch->pgid = branch->pgid;
		branch->background = check_background(next_branch, list_branch->next);
		return (branch->background);
	}
	return (false);
}

/*
** check_andor:
**
** For the given branch, check if it should be run according to
** the expect sequence of commands and the current last status.
*/

t_bool		check_andor(t_acb *branch)
{
	if (ft_strequ(branch->begin_andor, "CMDAND") && g_last_status != 0)
		return (false);
	else if (ft_strequ(branch->begin_andor, "CMDOR") && g_last_status == 0)
		return (false);
	return (true);
}
