/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   determine_bytes.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: simrossi <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/27 15:04:52 by simrossi     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/17 13:40:47 by simrossi    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "tmpsh.h"
#include "libft.h"
#include "argv_formater.h"
#include "assignation.h"
#include "forker.h"
#include "fd_management.h"
#include "setup_redirection.h"
#include "exec_file.h"
#include "reset_signals.h"
#undef stdout
#undef stdin

/*
** run_builtin:
**
** Run builtin commands from the builtin module.
** Format the python command to execute and execute it.
** Save, modify and restore the global environnement if needed.
*/

static int		run_builtin(t_acb *branch, char **cmd_args, t_pylst *variables)
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
	builtin = search_value(g_builtins, cmd_args[0]);
	save_std_fd(save);
	replace_std_fd(branch->stdin, branch->stdout);
	if (setup_redirection(branch) == true)
		status = builtin(cmd_args + 1, g_environ);
	else
		status = 1;
	save_std_fd(restore);
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

int				prepare_builtin(t_acb *branch, char *executable, \
		char **argv, t_pylst *variables)
{
	pid_t	pid;

	pid = -1;
	if (in(branch->tag_end, "BACKGROUND_JOBS", "PIPE", NULL))
	{
		if ((pid = fork_prepare(branch->pgid, branch->background)) == 0)
			exit(run_builtin(branch, argv, variables));
		else
		{
			close_branch_stdfd(branch);
			branch->running = true;
			free_pylst(&variables, pid);
			return (ft_strdel(&executable), pid);
		}
	}
	branch->status = run_builtin(branch, argv, variables);
	return (ft_strdel(&executable), pid);
}

/*
** child_execution:
**
** Run a builtin, or fork + execve a given executable.
** Setup redirection and change stdin/stdout as needed by any kind of pipe.
** Setup list of variables as environnement variables.
*/

static int		child_execution(t_acb *branch, char **argv, t_pylst *variables)
{
	pid_t		pid;
	char		*executable;

	executable = get_execname(argv[0]);
	if (executable && !ft_strchr(executable, '/'))
		return (prepare_builtin(branch, executable, argv, variables));
	if ((pid = fork_prepare(branch->pgid, branch->background)) == 0)
	{
		reset_signals();
		replace_std_fd(branch->stdin, branch->stdout);
		if (setup_redirection(branch) == false)
			exit(1);
		variables_config(variables, true);
		if (!executable)
			exit(127);
		if (execve(executable, argv, g_environ) == -1)
			exit(-1);
	}
	close_branch_stdfd(branch);
	branch->running = true;
	free_pylst(&variables, pid);
	return (ft_strdel(&executable), pid);
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
			variables_config(variables, false);
		if (redirection_prepare_fds(branch->redirectionfd))
			redirection_close_fds(branch->redirectionfd);
		branch->status = 0;
	}
	else
		branch->pid = child_execution(branch, cmd_args, variables);
	free_str_array(&cmd_args, 0);
}
