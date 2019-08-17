#include <sys/wait.h>
#include "tmpsh.h"
#include "libft.h"
#include "heredoc_apply.h"
#include "tagstoken_replacement.h"
#include "variables.h"
#include "cmdsubst_replacement.h"
#include "cmdsubst_runner.h"

/*
** get_quote_content:
**
** Concat the content of the tagstoken inside a quote's subast.
*/

static char		*get_quote_content(t_ast *subast)
{
	t_acb	*quote_branch;

	quote_branch = subast->list_branch->value;
	return (join_pylst(quote_branch->tagstokens->tokens, ""));
}

/*
** rstrip:
**
** Remove all newline at the end of the string.
*/

static void		rstrip(char *str)
{
	int		index;

	index = ft_strlen(str) - 1;
	while (index >= 0 && str[index] == '\n')
		str[index--] = '\0';
}

/*
** retrieve_content:
**
** For the given subast, format the content of the substitution
** according to the subast type.
*/

static char		*retrieve_content(t_ast *subast)
{
	char	*tmp_str;
	char	*content;

	content = NULL;
	if (ft_strequ(subast->type, "QUOTE"))
		content = get_quote_content(subast);
	else if (ft_strequ(subast->type, "CMDSUBST1"))
	{
		content = fd_readfile(subast->link_fd);
		waitpid(subast->pid, 0, WUNTRACED);
		rstrip(content);
	}
	else if (ft_strequ(subast->type, "CMDSUBST2") || \
			ft_strequ(subast->type, "CMDSUBST3"))
	{
		tmp_str = ft_itoa(subast->link_fd);
		content = ft_strjoin("/dev/fd/", tmp_str);
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

/*
** perform_subast_replacement:
**
** Inside a branch, replace each subast element by the generated content
** or the cmdsubst /dev/fd file.
*/

void			perform_subast_replacement(t_acb *branch)
{
	int		index;
	char	*content;
	t_ast	*subast;

	prepare_cmd_subst(branch);
	heredoc_apply(branch->redirectionfd, perform_subast_replacement);
	index = 0;
	while (iter_pylst(branch->subast, (void **)&subast))
	{
		content = retrieve_content(subast);
		if (content)
			replace_subast(branch, index++, content);
	}
}
