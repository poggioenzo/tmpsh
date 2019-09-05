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
#include "redirection_opener.h"
#include "fd_management.h"

static int		is_heredoc(char *type)
{
	return (in(type, "HEREDOC", "TRIPLEHEREDOC", "HEREDOCMINUS", NULL));
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

static char		*join_cmd(t_pylst *list_branch)
{
	char			*final_cmd;
	t_acb			*branch;
	size_t			index;
	char			*token;
	char			*tag;

	final_cmd = ft_strnew(0);
	while (iter_pylst(list_branch, (void **)&branch))
	{
		index = 0;
		while (index < branch->tagstokens->length)
		{
			tag = vindex_pylst(branch->tagstokens->tags, index);
			if (in(tag, "STMT", "SPACES", NULL))
			{
				token = vindex_pylst(branch->tagstokens->tokens, index);
				final_cmd = ft_fstrjoin(&final_cmd, &token, true, false);
			}
			index++;
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

	while (iter_pylst(branch->redirectionfd, (void **)&redirection))
	{
		if (is_heredoc(redirection->type))
			prepare_heredoc(redirection);
		else
			open_redirection_file(redirection);
		if (redirection->error == false)
		{
			if (redirection->dest)
				replace_fd(clean_popper(redirection->dest), \
						redirection->source);
			if (redirection->close)
				close(redirection->source);
		}
		else
			return (false);
	}
	return (true);
}
