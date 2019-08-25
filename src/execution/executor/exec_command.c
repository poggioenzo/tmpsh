#include "tmpsh.h"
#include "libft.h"
#include "argv_formater.h"
#include "assignation.h"
#include "forker.h"
#include "fd_management.h"
#include "setup_redirection.h"
#include "exec_file.h"
#undef stdout
#undef stdin

/*
** run_builtin:
**
** Run builtin commands from the builtin module.
** Format the python command to execute and execute it.
** Save, modify and restore the global environnement if needed.
*/

static int		run_builtin(char **cmd_args, t_pylst *variables)
{
	char	**saved_environ;
	int		(*builtin)(char **, char **);
	int		status;

	saved_environ = NULL;
	if (len_pylst(variables) > 0)
	{
		saved_environ = ft_duparray(g_environ);
		variables_config(variables, true);
		free_pylst(&variables, 0);
	}
	builtin = (int (*)(char **, char **))search_value(g_builtins, cmd_args[0]);
	status = builtin(cmd_args + 1, g_environ);
	if (saved_environ)
	{
		free_str_array(&g_environ, 0);
		g_environ = saved_environ;
	}
	return (status);
}

/*
** close_branch_stdfd:
**
** Close stdandard input/output of a branch, if given.
*/

static void		close_branch_stdfd(t_acb *branch)
{
	if (branch->stdin != -1)
		close(branch->stdin);
	if (branch->stdout != -1)
		close(branch->stdout);
}

/*
** child_execution:
**
** Run a builtin, or fork + execve a given executable.
** Setup redirection and change stdin/stdout as needed by any kind of pipe.
** Setup list of variables as environnement variables.
*/

// Need to recode reset_signals
static int		child_execution(t_acb *branch, char **argv, t_pylst *variables)
{
	pid_t		pid;
	char		*executable;

	if (search_value(g_builtins, argv[0]))
	{
		branch->status = run_builtin(argv, variables);
		return (-1);
	}
	pid = fork_prepare(branch->pgid, branch->background);
	if (pid == 0)
	{
		reset_signals();
		replace_std_fd(branch->stdin, branch->stdout);
		setup_redirection(branch);
		variables_config(variables, true);
		executable = get_execname(argv[0]);
		if (!executable)
			exit(127);
		if (execve(executable, argv, g_environ) == -1)
			exit(-1);
	}
	close_branch_stdfd(branch);
	branch->running = true;
	return (pid);
}

/*
** exec_command:
**
** Use to run a simple command, the branch element which is not
** a SUBSH or a CURSH.
** Prepare command variables, run within the shell if the command is a
** builtin, fork otherwise if it's needed.
** Manage command filedescriptors/pipes.
*/

void			exec_command(t_acb *branch)
{
	t_pylst		*variables;
	char		**cmd_args;

	variables = retrieve_assignation(branch);
	cmd_args = extract_cmd(branch);
	if (ft_arraylen(cmd_args) == 0)
	{
		close_branch_stdfd(branch);
		if (len_pylst(variables) >= 1)
		{
			variables_config(variables, false);
			branch->status = 0;
		}
	}
	else
		branch->pid = child_execution(branch, cmd_args, variables);
}
