#include "tmpsh.h"
#include "libft.h"

int		built_jobs(char **argv, char **environ)
{
	t_pylst		*job;
	t_acb		*command_branch;

	while (iter_pylst(g_jobs->list_jobs, (void **)&jobs))
	{
		command_branch = (t_acb *)index_pylst(jobs, -1)->value;
		ft_printf("[%d] : %s\n", command_branch->pid, command_branch->command);
	}
	return (0);
}

int		built_fg(char **argv, char **environ)
{

	if (ft_arraylen(argv) == 0)
		index = 0;
}
