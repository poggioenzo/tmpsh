
#include "tmpsh.h"
#include "libft.h"

t_ht_table	*g_builtins = NULL;

/*
** prev_is_stmt:
**
** Check in the given tag list if the previous element is a STMT.
*/

int		prev_is_stmt(t_pylst *tags, int index)
{
	char	*prev_tag;

	prev_tag = index_pylst(tags, index - 1)->value;
	return (ft_strequ(prev_tag, "STMT"))
}

/*
** join_stmt:
**
** If a STMT is following an other STMT, concat them in a single token.
*/

void	join_stmt(t_acb *branch)
{
	int		index;
	t_tagstokens	*tagstok;
	char	*curr_tag;
	char	*prev_token;
	char	*new_stmt;

	tagstok = branch->tagstokens;
	while (index < tagstok->length)
	{
		curr_tag = index_pylst(tagstok->tags, index)->value;
		if (ft_strequ(curr_tag, "STMT") && prev_is_stmt(curr_tag, "STMT"))
		{
			prev_token = index_pylst(tagstok->tokens, index - 1);
			new_stmt = ft_strjoin(prev_token->value, prev_token->next->value);
			pylst_replace(tagstok->tokens, index - 1, new_stmt, NO_COPY_BUT_FREE, \
					_chare);
			del_portion_pylst(&pylst, index, index + 1);
			//update_length(tagstok);
			index--;
		}
		index++;
	}
}

/*
** convert_command:
**
** Convert a command in a pylst format into a char ** format, like argv.
*/

char		**convert_command(t_pylst *command)
{
	char	**cmd_array;
	char	*value;
	int		index;

	cmd_array = ft_memalloc(sizeof(char *) * (len_pylst(command) + 1));
	index = 0;
	while (pylst_iter(command, &value))
		cmd_array[index++] = ft_strdup(value);
	cmd_array[index] = NULL;
	free_pylst(&command);
	return (cmd_array);
}

/*
** extract_cmd:
**
** Get only token used to run a command, format argv + environ.
*/

char		**extract_cmd(t_acb *branch)
{
	int		index;
	t_pylst		*command;
	char		*tag;
	char		*token;

	join_stmt(branch);
	index = 0;
	command = NULL;
	while (index < branch->tagstokens->length)
	{
		tag = index_pylst(branch->tags, index)->value;
		if (ft_strequ(tag, "STMT"))
		{
			token = index_pylst(branch->tokens, index)->value;
			push_pylst(&command, token, ft_strlen(token) + 1, _chare);
		}
		index++;
	}
	return (convert_command(command));
}

/*
** run_builtin:
**
** Run builtin commands from the builtin module.
** Format the python command to execute and execute it.
** Save, modify and restore the global environnement if needed.
*/

int		run_builtin(char **cmd_args, t_pylst *variables)
{
	char	**saved_environ;
	int		(*builtin)(char **, char **);
	int		status;

	saved_environ = NULL;
	if (len_pylst(variables) > 0)
	{
		saved_environ = ft_duparray(g_environ);
		variables_config(variables);
		free_pylst(&variables);
	}
	// NEED TO SETUP BUILTINS HASHTABLE
	builtin = search_value(g_grammar->builtins, cmd_args[0]);
	status = builtin(cmd_args + 1, g_environ);
	if (saved_environ)
	{
		free_str_array(&g_environ);
		g_environ = saved_environ;
	}
	return (status);
}

/*
** close_branch_stdfd:
**
** Close stdandard input/output of a branch, if given.
*/

static void		close_branch_stdfd(t_act *branch)
{
	if (branch->stdin >= 0)
		close(branch->stdin);
	if (branch->stdout >= 0)
		close(branch->stdout);

}

/*
** child_execution:
**
** Run a builtin, or fork + execve a given executable.
** Setup redirection and change stdin/stdout as needed by any kind of pipe.
** Setup list of variables as environnement variables.
*/

int		child_execution(t_acb *branch, char **argv, t_pylst *variables)
{
	pid_t		pid;

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
	else
	{
		close_branch_stdfd(branch);
		return (pid);
	}
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

void	exec_command(t_acb *branch)
{
	t_pylst		*variables;
	char		**cmd_args;

	variables = retrieve_assignation(branch);
	cmd_args = extract_cmd(branch);
	if ft_arraylen(cmd_args) == 0
	{
		close_branch_stdfd(branch);
		if (len_pylst(variables) >= 1)
		{
			variables_config(variables);
			branch->status = 0;
		}
	}
	else
		branch->pid = child_execution(branch, cmd_args, variables);
}
