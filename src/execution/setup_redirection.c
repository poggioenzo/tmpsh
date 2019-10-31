/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   determine_bytes.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: simrossi <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/27 15:04:52 by simrossi     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/28 10:20:48 by epoggio     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "tmpsh.h"
#include "libft.h"
#include "redirection_opener.h"
#include "fd_management.h"
#include "iter_tagstokens.h"
#include "heredoc_apply.h"

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

static char		*join_cmd(t_pylst *list_branch)
{
	char			*final_cmd;
	t_acb			*branch;
	char			*token;
	char			*tag;

	final_cmd = ft_strnew(0);
	while (iter_pylst(list_branch, (void **)&branch))
	{
		while (iter_tagstokens(branch->tagstokens, &token, &tag))
		{
			if (in(tag, "STMT", "SPACES", NULL))
				final_cmd = ft_fstrjoin(&final_cmd, &token, true, false);
		}
		token = "\n";
		final_cmd = ft_fstrjoin(&final_cmd, &token, true, false);
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

static void		prepare_heredoc(t_redirection_fd *redirection)
{
	int		here_pipe[2];
	char	*content;

	setup_pipe_fd(here_pipe);
	redirection->dest = int_copy(here_pipe[0]);
	if (ft_strequ(redirection->type, "TRIPLEHEREDOC"))
		content = ft_strjoin(redirection->tagstokens->tokens->value, "\n");
	else
		content = join_cmd(redirection->heredoc_ast->list_branch);
	write(here_pipe[1], content, ft_strlen(content));
	ft_strdel(&content);
	close(here_pipe[1]);
}

void			redirection_close_fds(t_pylst *redirection_list)
{
	t_redirection_fd	*tmp_redir;
	int					index;
	int					nbr_redir;

	index = 0;
	nbr_redir = len_pylst(redirection_list);
	while (index < nbr_redir)
	{
		tmp_redir = vindex_pylst(redirection_list, index++);
		if (tmp_redir->error == true)
			return ;
		if (tmp_redir->dest)
		{
			close(clean_popper(tmp_redir->dest));
			tmp_redir->dest = NULL;
		}
	}
}

t_bool			redirection_prepare_fds(t_pylst *redirection_list)
{
	t_redirection_fd	*tmp_redir;
	int					index;
	int					nbr_redir;

	index = 0;
	nbr_redir = len_pylst(redirection_list);
	while (index < nbr_redir)
	{
		tmp_redir = vindex_pylst(redirection_list, index++);
		if (is_heredoc(tmp_redir->type))
			prepare_heredoc(tmp_redir);
		else
			open_redirection_file(tmp_redir);
		if (tmp_redir->error == true)
		{
			redirection_close_fds(redirection_list);
			return (false);
		}
	}
	return (true);
}

/*
** setup_redirection:
**
** @branch: Single branch to prepare redirection.
**
** Go through each redirection of a given branch, and set them up.
** Prepare the destination before applying dup2.
*/

t_bool			setup_redirection(t_acb *branch)
{
	t_redirection_fd	*redirection;
	int					dest_fd;

	if (redirection_prepare_fds(branch->redirectionfd) == false)
		return (false);
	while (iter_pylst(branch->redirectionfd, (void **)&redirection))
	{
		if (redirection->dest)
		{
			dest_fd = clean_popper(redirection->dest);
			if (replace_fd(dest_fd, redirection->source,
						redirection->close_dst) == -1)
			{
				branch->redirectionfd->iter_item = NULL;
				ft_dprintf(2, NAME_SH" %d: bad file descriptor\n", dest_fd);
				return (false);
			}
			redirection->dest = NULL;
		}
		if (redirection->close_src)
			close(redirection->source);
	}
	return (true);
}
