
static void		setup_branch_pipe(t_ast *ast, int index, t_acb *branch)
{
	t_acb	*next_branch;
	int		new_pipe[2];

	next_branch = index_pylst(ast->list_branch, index + 1)->value;
	setup_pipe_fd(new_pipe);
	next_branch->stdin = new_pipe[0];
	branch->stdout = new_pipe[1];
}

void		run_ast(t_ast *ast)
{
	t_pylst	*job_list;
	int		index;
	int		nbr_branch;
	t_acb	*branch;

	index = 0;
	nbr_branch = len_pylst(ast.list_branch);
	job_list = NULL;
	while (index < nbr_branch)
	{
		branch = (t_acb *)index_pylst(ast->list_branch, index)->value;
		push_pylst(&job_list, branch, 0, _ptr);
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
		analyse_branch_result(branch, job_list);
		index++;
	}
	wait_zombie();
}

void	analyse_branch_result(t_acb *branch, t_pylst **job_list)
{
	try_set_job_pgid(*job_list);
	if (ft_strequ(branch->tag_end, "BACKGROUND_JOBS"))
	{
		g_last_status = 0;
		add_job(*job_list);
	}
	else if (ft_strequ(branch->tag_end, "PIPE"))
	{
		if (analyse_job_status(job_list) == running)
			add_job(*job_list);
		if (branch->background == false && g_jobs->allow_background == true)
		{
			set_foreground(getpgrp());
			restore_tcattr();
		}
		g_last_status = branch->status;
	}
	if (ft_strequ(branch->tag_end))
		free_pylst(job_list);
}

void	try_set_job_pgid(t_pylst *job_list)
{
	int		index;
	pid_t	pgid;
	int		nbr_job;
	t_acb	*job;

	if (((t_acb *)job_list->value)->pgid != 0)
		return ;
	index = 0;
	nbr_job = len_pylst(job_list);
	pgid = 0;
	while (index < nbr_job && pgid == 0)
	{
		job = (t_acb *)index_pylst(job_list, index)->value;
		if (job->pid != -1)
			pgid = getpgid(job->pid);
		index++;
	}
	if (pgid == 0)
		return ;
	while (iter_pylst(job_list, (void **)&job))
		job->pgid = pgid;
}

void	close_subast_pipe(t_acb *branch)
{
	int		index;
	int		nbr_subast;
	t_ast	*subast;

	while (iter_pylst(branch->subast, (void **)&subast))
	{
		if (ft_start_with(subast->type, "CMDSUBST"))
			close(subast->link_fd);
		else if (ft_strequ(subast->type, "DQUOTES"))
			close_subast_pipe((t_acb *)subast->list_branch->value);
	}
}

t_bool	check_background(t_pylst *list_branch, int index)
{
	t_acb	*branch;
	t_acb	*next_branch;

	branch = (t_acb *)index_pylst(list_branch, index)->value;
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
		next_branch = (t_acb *)index_pylst(list_branch, index + 1)->value;
		next_branch->pgid = branch->pgid;
		branch->background = check_background(list_branch, index + 1);
		return (branch->background);
	}
	return (false);
}

t_bool		check_andor(t_acb *branch)
{
	if (ft_strequ(branch->begin_andor, ""))
		return (true);
	if (ft_strequ(branch->begin_andor, "CMDAND") && g_last_status == 0)
		return (true);
	else if (ft_strequ(branch->begin_andor, "CMDOR") && g_last_status != 0)
		return (true);
	return (false);
}

t_pylst		*prepare_cmdsubst_pipe(void)
{
	int		pipe_fd[2];
	t_pylst	*pipe_lst;
	int		stdin;
	int		stdout;

	setup_pipe_fd(pipe_fd);
	pipe_lst = NULL;
	stdin = pipe_fd[0];
	stdout = pipe_fd[1];
	push_pylst(&pipe_lst, &stdin, 0, _ptr);
	push_pylst(&pipe_lst, &stdout, 0, _ptr);
}

void	run_cmdsubst(t_ast *subast)
{
	t_pylst	*pipe_fd;
	pid_t	pid;
	int		stdin;
	int		stdout;

	pipe_fd = prepare_cmdsubst_pipe();
	pid = fork_prepare(getpgrp(), false);
	if (pid == 0)
	{
		clear();
		g_jobs->allow_background = false;
		change_sigmask(SIGTSTP, SIG_BLOCK);
		stdin = -1;
		stdout = -1;
		if (ft_strequ(subast->type, "CMDSUBST2"))
			stdin = *pylst_pop(pipe_fd, 0);
		else if (ft_strequ(subast->type, "CMDSUBST1") || \
				ft_strequ(subast->type, "CMDSUBST3"))
			stdout = *pylst_pop(pipe_fd, 1);
		replace_std_fd(stdin, stdout);
		close(*pylst_pop(pipe_fd, 0));
		run_ast(subast);
		exit(g_last_status);
	}
	else
	{
		subast->pid = pid;
		if (ft_strequ(subast->type, "CMDSUBST2"))
			subast->link_fd = *pylst_pop(pipe_fd, 1);
		else
			subast->link_fd = *pylst_pop(pipe_fd, 0);
		close(*pylst_pop(pipe_fd, 0));
	}
}

void	prepare_cmd_subst(t_acb *branch)
{
	t_ast	*subast;

	heredoc_apply(branch->redirectionfd, prepare_cmd_subst);
	while (iter_pylst(branch->subast, (void **)&subast))
	{
		if (ft_start_with(subast->type, "CMDSUBST"))
			run_cmdsubst(subast);
		else if (ft_strequ(subast->type, "DQUOTES"))
			prepare_cmd_subst((t_acb *)subast->list_branch->value);
	}
}

void	replace_redirection(t_acb *branch, int change_index, char *content)
{
	char				*tag;
	char				*token;
	t_redirection_fd	*redirection;
	while (iter_pylst(branch->redirectionfd, &redirection))
	{
		tag = (char *)redirection->tagstokens->tags->value;
		token = (char *)redirection->tagstokens->tokens->value;
		if (ft_strequ(tag, "SUBAST") && ft_atoi(token) == change_index)
			redirection->dest = content;
	}

}

void	replace_subast(t_acb *branch, int change_index, char *content)
{
	int		index;
	char	*tag;
	char	*token;
	t_tagstokens	*tagstok;

	index = 0;
	tagstok = branch->tagstokens;
	while (index < tagstok->length)
	{
		tag = (char *)index_pylst(tagstok->tags, index)->value;
		token = (char *)index_pylst(tagstok->tokens, index)->value;
		if (ft_strequ(tag, "SUBAST") && ft_atoi(token) == change_index)
		{
			update_pylst(tagstok->tokens, index, content, \
					sizeof(char) * (ft_strlen(content) + 1), _chare);
			update_pylst(tagstok->tags, index, "STMT", 0, _chare);
			return ;
		}
		index++;
	}
	replace_redirection(branch, change_index, content);
}

char	*get_quote_content(t_ast *subast)
{
	t_acb	*quote_branch;

	quote_branch = subast->list_branch->value;
	return (join_pylst(quote_branch->tagstokens->tokens, ""));
}

static void		rstrip(char *str)
{
	int		index;

	index = ft_strlen(str) - 1;
	while (index >= 0 && str[index] == '\n')
		str[index--] = '\0';
}

char	*retrieve_content(t_ast *subast)
{
	char	*tmp_str;
	char	*content;

	content = NULL;
	if (ft_strequ(subast->type, "QUOTE"))
		content = get_quote_content(subast);
	else if (ft_strequ(subast->type, "CMDSUBST1"))
	{
		content = readfile(subast->link_fd);
		waitpid(subast->pid, WUNTRACED);
		rstrip(content);
	}
	else if (ft_strequ(subast->type, "CMDSUBST2") || \
			ft_strequ(subast->type, "CMDSUBST3"))
	{
		tmp_str = ft_itoa(subast->link_fd);
		content = ft_strjoin("/dev/fd/" + str_link_fd);
		ft_strdel(&tmp_str);
	}
	else if (ft_strequ(subast->type, "BRACEPARAM"))
	{
		tmp_str = ((t_acb *)subast->list_branch->value)->tagstokens->tokens->value;
		content = ft_strdup(retrieve_variable(tmp_str));
	}
	else if (ft_strequ(subast->type, "DQUOTES"))
	{
		perform_subast_replacement(subast->list_branch->value);
		content = get_quote_content(subast);
	}
	return (content);
}

void	perform_subast_replacement(t_acb *branch)
{
	int		index;
	char	*content;
	t_ast	*subast;

	prepare_cmd_subst(branch);
	heredoc_apply(branch->redirectionfd, perform_subast_replacement);
	index = 0;
	while (iter_pylst(branch->subast, &subast))
	{
		content = retrieve_content(subast);
		if (content)
			replace_subast(branch, index++, content);
	}
}

pid_t	run_subshell(t_acb *branch, t_ast *subast)
{
	pid_t	pid;

	pid = fork_prepare(branch->pgid, branch->background);
	if (pid == 0)
	{
		setup_redirection(branch);
		reset_signals();
		clear();
		g_jobs->allow_background = false;
		replace_std_fd(branch->stdin, branch->stdout);
		run_ast(subast);
		exit(g_last_status);
	}
	else
	{
		if (branch->stdin >= 0)
			close(branch->stdin);
		if (branch->stdout >= 0)
			close(branch->stdout);
		return (pid);
	}
}

static int		is_bg_or_pipe(t_acb *branch)
{
	return (ft_strequ(branch->tag_end, "BACKGROUND_JOBS") || \
			ft_strequ(branch->tag_end, "PIPE"));
}

t_bool		perform_command_as_subast(t_acb *branch)
{
	int		index;
	int		nbr_subast;
	t_ast	*subast;

	index = 0;
	nbr_subast = len_pylst(branch->subast);
	while (index < nbr_subast)
	{
		subast = index_pylst(branch->subast, index);
		if (ft_strequ(subast->type, "CURSH") || ft_strequ("SUBSH"))
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
