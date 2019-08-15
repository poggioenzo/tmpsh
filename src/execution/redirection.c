#include <unistd.h>
#include "libft.h"
#include "fd_management.h"

int		need_open_file(char *type)
{
	return (ft_strequ(type, "TRUNC") || ft_strequ(type, "APPEND") || \
			ft_strequ(type, "READ_FROM"));
}

int		is_heredoc(char *type)
{
	return (ft_strequ(type, "HEREDOC") || ft_strequ(type, "TRIPLEHEREDOC") || \
			ft_strequ(type, "HEREDOCMINUS"));
}

/*
** convert_dest:
**
** Retrieve the int value of the string redirection->dest.
*/

static void		*convert_dest(t_redirection_fd *redirection)
{
	int		dest_fd;

	if (ft_isdigit(redirection->dest))
	{
		dest_fd = ft_atoi(redirection->dest);
		redirection->dest = &dest_fd;
	}
	else
		redirection->dest = NULL;
}

/*
** open_redirection_file:
**
** For a given redirection, open the destination file with
** the expected mode.
*/

void	open_redirection_file(t_redirection_fd *redirection)
{
	int		fd;
	int		flags;

	if (need_open_file(redirection->type))
	{
		flags = 0;
		if (access(redirection->dest, F_OK) == -1)
			flags |= O_CREAT;
		if (ft_strequ(redirection->type, "TRUNC"))
			flags |= O_WRONLY;
		else if (ft_strequ(redirection->type, "APPEND"))
			flags |= O_WRONLY | O_APPEND;
		else if (ft_strequ(redirection->type, "READ_FROM"))
			flags |= O_RDONLY;
		if ((fd = open(redirection->dest, flags, 0666)) != -1)
			redirection->dest = &fd;
		else
		{
			ft_dprintf(STDERR_FILENO, "tmpsh: permission denied: %s\n", \
					redirection->dest);
			redirection->error = true;
		}
	}
	else
		convert_dest(redirection);
}

/*
** join_cmd:
**
** @list_branch: each branch of the heredoc ast.
**
** From the given list_branch of the heredoc ast, join each token
** to retrieve a single string containing the content to use.
**
** return: - a string containing the heredoc content 
*/

char	*join_cmd(const t_pylst *list_branch)
{
	char	*final_cmd;
	t_acb	*branch;
	int		index;
	t_tagstokens	*tagstok;
	char		*tag;

	final_cmd = ft_strnew(0);
	while (pylst_iter(list_branch, branch))
	{
		index = 0;
		tagstok = branch->tagstokens;
		while (index < tagstok->length)
		{
			tag = index_pylst(index)->value;
			if (ft_strequ(tag, "STMT") || ft_strequ(tag, "SPACES"))
				final_cmd = ft_fstrjoin(&final_cmd, &tag, true, false);
			index++;
		}
		tag = "\n";
		final_cmd = ft_fstrjoin(&final_cmd, &tag, true, false);
	}
	return (final_cmd);
}

/*
** prepare_heredoc:
**
** @redirections: Heredoc element to setup.
**
** Prepare the source and dest of the redirection. Openning
** a pipe a giving him the entire content of the heredoc.
*/

void	prepare_heredoc(t_redirection_fd *redirection)
{
	int		here_pipe[2];

	setup_pipe_fd(here_pipe);
	redirection->source = 0;
	redirection->dest = here_pipe[0];
	content = join_cmd(redirection->heredoc_ast->list_branch);
	write(here_pipe[1], content, ft_strlen(content));
	close(here_pipe[1]);
}

/*
** heredoc_apply:
**
** @redirections_list: All redirection of a branch.
** @func: Function to apply on each heredoc.
**
** Go through each redirection of a single branch, and apply
** the given function on each available HEREDOC.
*/

void	heredoc_apply(t_pylst *redirections_list, void (*func)(t_acb *))
{
	t_redirection_fd	*redirection;
	t_acb				*redir_branch;

	redirection = NULL;
	while (pylst_iter(redirections_list, &redirection))
	{
		if (ft_strequ(redirection->type, "HEREDOC"))
		{
			while (pylst_iter(redirection->heredoc_ast->list_branch, &redir_branch))
				func(redir_branch);
		}
	}
}

/*
** setup_redirection:
**
** @branch: Single branch to prepare redirection.
**
** Go through each redirection of a given branch, and set them up.
** Prepare the destination before applying dup2.
*/

void	setup_redirection(t_acb *branch)
{
	t_pylst		*fd_list;
	int			index;
	int			nbr_redirection;
	t_redirection_fd	*redirection;

	fd_list = branch->redirectionfd;
	index = 0;
	nbr_redirection = len_pylst(fd_list);
	while (pylst_iter(fd_list, &redirection))
	{
		if (is_heredoc(redirection->type))
			prepare_heredoc(redirection);
		else
			open_redirection_file(redirection);
		if (redirection->error == false)
		{
			if (redirection->dest)
				replace_fd(*redirection->dest, redirection->source);
			if (redirection->close)
				close(redirection->source);
		}
	}
}
