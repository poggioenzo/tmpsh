#include "tmpsh.h"
#include "libft.h"
#include "run_ast_utils.h"
#include "foreground.h"
#include "job_control.h"
#include "variable_replacement.h"
#include "cmdsubst_replacement.h"
#include "subast_command.h"
#include "exec_command.h"

/*
** try_set_job_pgid:
**
** From a given list, try to set up his pgid for each
** job whenever a pid is available.
** Avoid to search pgid if already set.
*/

static void		try_set_job_pgid(t_pylst *job_branches)
{
	int		index;
	pid_t	pgid;
	int		nbr_job;
	t_acb	*branch;

	if (((t_acb *)job_branches->value)->pgid != 0)
		return ;
	index = 0;
	nbr_job = len_pylst(job_branches);
	pgid = 0;
	while (index < nbr_job && pgid == 0)
	{
		branch = vindex_pylst(job_branches, index);
		if (branch->pid != -1)
			pgid = getpgid(branch->pid);
		index++;
	}
	if (pgid == 0)
		return ;
	while (iter_pylst(job_branches, (void **)&branch))
		branch->pgid = pgid;
}

/*
** analyse_branch_result:
**
** Whenever a branch have been executed, behave depending of the branch
** configuration.
** Wait the child process if needed, add the current jobs_list in
** background otherwise.
** Retrieve the foreground for the shell if possible.
*/

static void		analyse_branch_result(t_acb *branch, t_pylst **job_list)
{
	try_set_job_pgid(*job_list);
	if (ft_strequ(branch->tag_end, "BACKGROUND_JOBS"))
	{
		g_last_status = 0;
		add_job(job_list);
	}
	else if (!ft_strequ(branch->tag_end, "PIPE"))
	{
		if (analyse_job_status(*job_list, WUNTRACED) == running)
			add_job(job_list);
		if (branch->background == false && g_jobs->allow_background == true)
		{
			set_foreground(getpgrp());
			restore_tcattr();
		}
		g_last_status = branch->status;
	}
	if (!ft_strequ(branch->tag_end, "PIPE"))
		free_pylst(job_list, 0);
}

/*
** run_ast:
**
** Main function to run an entire AST instance in a
** recursive way.
** Go through each branch and run them one by one (or more),
** running each time the contained command.
*/

void			run_ast(t_ast *ast)
{
	t_pylst	*job_list;
	int		index;
	int		nbr_branch;
	t_acb	*branch;

	index = 0;
	nbr_branch = len_pylst(ast->list_branch);
	job_list = NULL;
	while (index < nbr_branch)
	{
		branch = vindex_pylst(ast->list_branch, index);
		push_pylst(&job_list, branch, 0, _ptr); //Need to use branch ??
		replace_variable(branch);
		if (check_andor(branch) == false)
		{
			index++;
			free_pylst(&job_list, 0);
			continue ;
		}
		perform_subast_replacement(branch);
		branch->pgid = ((t_acb *)job_list->value)->pgid;
		check_background(ast->list_branch, index);
		if (ft_strequ(branch->tag_end, "PIPE"))
			setup_branch_pipe(ast, index, branch);
		if (perform_command_as_subast(branch) == false)
			exec_command(branch);
		close_subast_pipe(branch);
		analyse_branch_result(branch, &job_list);
		index++;
	}
}

void		executor(t_ast *ast)
{
	wait_zombie();
	run_ast(ast);
}
