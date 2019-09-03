#include "tmpsh.h"
#include "libft.h"
#include "variables.h"
#include "heredoc_apply.h"
#include "replace_home.h"
#include "substitution_insert.h"
#include "variable_replacement.h"
#include "tagstokens.h"
#include "join_stmt.h"

/*
** variable_replacement.c
**
** Use to replace inside tagstoken variable element, when
** a token look like $VARIABLE only (without "${VAR}").
**
** Manage the replacement of local and environnement variable.
*/

/*
** tagstoken_variable_swap:
**
** @tagstok: tagstokens where replacement have to be done.
** @index: Index of the given VAR tag.
**
** Whenever a VAR tag is found, found the corresponding value
** and remplace it inside the tagstokens element.
*/

static void		tagstoken_variable_swap(t_tagstokens *tagstok, int index)
{
	char	*variable;
	char	*token;

	token = vindex_pylst(tagstok->tokens, index);
	variable = retrieve_variable(token + 1);
	substitution_insert(variable, tagstok, index);
	ft_strdel(&variable);
}

/*
** replace_tild:
**
** Whenever a STMT is found, check if it start with a '~', and if it the
** case perform the tild subsitution, if possible.
*/

static void		replace_tild(t_tagstokens *tagstok, int index)
{
	char	*token;
	char	*new_token;

	token = vindex_pylst(tagstok->tokens, index);
	if (token[0] != '~')
		return ;
	if (!(new_token = replace_home(token)))
		return ;
	update_pylst(tagstok->tokens, index, new_token, NO_COPY_BUT_FREE, _chare);
}

/*
** update_tagstokens:
**
** From a single tagstokens, go through each tokens and try to replace
** VAR tag.
** Check also if STMT tags contain have some tild to replace.
*/

void		update_tagstokens(t_tagstokens *tagstokens, t_acb *branch)
{
	size_t	index;
	int		index_subast;
	char	*tag;
	t_ast	*subast;

	index = 0;
	index_subast = 0;
	while (index < tagstokens->length)
	{
		tag = vindex_pylst(tagstokens->tags, index);
		if (ft_strequ(tag, "VAR"))
			tagstoken_variable_swap(tagstokens, index);
		else if (ft_strequ(tag, "STMT"))
			replace_tild(tagstokens, index);
		else if (branch && ft_strequ(tag, "SUBAST"))
		{
			subast = vindex_pylst(branch->subast, index_subast);
			if (ft_strequ(subast->type, "DQUOTES"))
				replace_variable(subast->list_branch->value);
			index_subast++;
		}
		index++;
	}
}

/*
** replace_variable:
**
** @branch: Branch where variable have to be replaced.
**
** Replace each variable inside a branch. Replace variable
** in the branch's tagstokens, and in redirections of the
** branch.
*/

void			replace_variable(t_acb *branch)
{
	t_redirection_fd	*redirection;

	heredoc_apply(branch->redirectionfd, replace_variable);
	while (iter_pylst(branch->redirectionfd, (void **)&redirection))
	{
		if (!in(redirection->type, "HEREDOCMINUS", "TRIPLEHEREDOC", NULL))
		{
			update_tagstokens(redirection->tagstokens, NULL);
			redirection->dest = vindex_pylst(redirection->tagstokens->tokens, \
					redirection->tagstokens->length - 1);
		}
	}
	update_tagstokens(branch->tagstokens, branch);
	join_stmt(branch);
}
