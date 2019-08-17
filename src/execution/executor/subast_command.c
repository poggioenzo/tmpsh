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
	return (ft_strequ(branch->tag_end, "BACKGROUND_JOBS") || \
			ft_strequ(branch->tag_end, "PIPE"));
}

/*
** perform_command_as_subast:
**
** If the command is composed of a SUBSH or a CURSH,
** create a layer for this kind of command and run them.
** If it's not run in a subshell, save and restore the initial
** stdin/stdout/stderr to prevent change during execution.
*/

t_bool		perform_command_as_subast(t_acb *branch)
{
	int		index;
	int		nbr_subast;
	t_ast	*subast;

	index = 0;
	nbr_subast = len_pylst(branch->subast);
	while (index < nbr_subast)
	{
		subast = index_pylst(branch->subast, index)->value;
		if (ft_strequ(subast->type, "CURSH") || ft_strequ(subast->type, "SUBSH"))
		{
			if (ft_strequ(subast->type, "CURSH") && !is_bg_or_pipe(branch))
			{
				save_std_fd(save);
				replace_std_fd(branch->stdin, branch->stdout);
				setup_redirection(branch);
				run_ast(subast);
				branch->pid = -1;
				save_std_fd(restore);
			}
			else
				branch->pid = run_subshell(branch, subast);
			return (true);
		}
		index++;
	}
	return (false);
}
