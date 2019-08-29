#include "tmpsh.h"
#include "libft.h"
#include "variables.h"
#include "heredoc_apply.h"
#include "replace_home.h"

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
	variable = retrieve_variable(token + 1); //Verify allocation
	update_pylst(tagstok->tokens, index, variable, NO_COPY_BUT_FREE, _chare);
	update_pylst(tagstok->tags, index, "STMT", 0, _ptr);
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
** replace_variable:
**
** @branch: Branch where variable have to be replaced.
**
** Replace each variable inside a branch->tagstokens with
** the associated value.
*/

void			replace_variable(t_acb *branch)
{
	size_t		index;
	int		index_subast;
	char	*tag;
	t_ast	*subast;

	heredoc_apply(branch->redirectionfd, replace_variable);
	index = 0;
	index_subast = 0;
	while (index < branch->tagstokens->length)
	{
		tag = vindex_pylst(branch->tagstokens->tags, index);
		if (ft_strequ(tag, "VAR"))
			tagstoken_variable_swap(branch->tagstokens, index);
		else if (ft_strequ(tag, "STMT"))
			replace_tild(branch->tagstokens, index);
		else if (ft_strequ(tag, "SUBAST"))
		{
			subast = vindex_pylst(branch->subast, index_subast);
			if (ft_strequ(subast->type, "DQUOTES"))
				replace_variable(subast->list_branch->value);
			index_subast++;
		}
		index++;
	}
}
