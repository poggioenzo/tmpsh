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
#include "fd_management.h"
#include "setup_redirection.h"
#include "run_ast.h"
#include "subshell.h"
#undef stdin
#undef stdout

/*
** is_bg_or_pipe:
**
** Check if the command in the branch is a pipe or a background command.
*/

static int		is_bg_or_pipe(t_acb *branch)
{
	if (branch->pgid != 0)
		return (1);
	return (in(branch->tag_end, "BACKGROUND_JOBS", "PIPE", NULL));
}

static void		run_cursh(t_acb *branch, t_ast *subast)
{
	save_std_fd(save);
	replace_std_fd(branch->stdin, branch->stdout);
	branch->pid = -1;
	if (setup_redirection(branch))
	{
		run_ast(subast);
		branch->status = g_last_status;
	}
	else
		branch->status = 1;
	save_std_fd(restore);
}

/*
** perform_command_as_subast:
**
** If the command is composed of a SUBSH or a CURSH,
** create a layer for this kind of command and run them.
** If it's not run in a subshell, save and restore the initial
** stdin/stdout/stderr to prevent change during execution.
*/

t_bool			perform_command_as_subast(t_acb *branch)
{
	int		index;
	int		nbr_subast;
	t_ast	*subast;

	index = 0;
	nbr_subast = len_pylst(branch->subast);
	while (index < nbr_subast)
	{
		subast = vindex_pylst(branch->subast, index);
		if (in(subast->type, "CURSH", "SUBSH", NULL))
		{
			if (ft_strequ(subast->type, "CURSH") && !is_bg_or_pipe(branch))
				run_cursh(branch, subast);
			else
			{
				branch->pid = run_subshell(branch, subast);
				branch->running = true;
			}
			return (true);
		}
		index++;
	}
	return (false);
}
