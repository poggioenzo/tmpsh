#include "tmpsh.h"
#include "libft.h"
#include "variables.h"
#include "heredoc_apply.h"

/*
** tagstoken_variable_swap:
**
** @tagstok: tagstokens where replacement have to be done.
** @index: Index of the given VAR tag.
**
** Whenever a VAR tag is found, found the corresponding value
** and remplace it inside the tagstokens element.
*/

static void		tagstoken_variable_swap(t_tagstokens *tagstok, int index, \
		char *tag)
{
	char	*variable;
	char	*token;

	token = (char *)index_pylst(tagstok->tokens, index)->value;
	variable = retrieve_variable(token + 1);
	update_pylst(tagstok->tokens, index, variable, NO_COPY_BUT_FREE, _chare);
	update_pylst(tagstok->tags, index, "STMT", 0, _ptr);
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
	int		index;
	int		index_subast;
	char	*tag;
	t_ast	*subast;

	heredoc_apply(branch->redirectionfd, replace_variable);
	index = 0;
	index_subast = 0;
	while (index < branch->tagstokens->length)
	{
		tag = index_pylst(branch->tagstokens->tags, index)->value;
		if (ft_strequ(tag, "VAR"))
			tagstoken_variable_swap(branch->tagstokens, index, tag);
		else if (ft_strequ(tag, "SUBAST"))
		{
			subast = (t_ast *)index_pylst(branch->subast, index_subast)->value;
			if (ft_strequ(subast->type, "DQUOTES"))
				replace_variable(subast->list_branch->value);
			index_subast++;
		}
		index++;
	}
}
