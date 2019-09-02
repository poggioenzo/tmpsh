#include "tmpsh.h"
#include "libft.h"
#include "substitution_insert.h"

/*
** replace_redirection:
**
** If the replacement is not done in the branch tagstokens,
** search if the replacement can be done inside a redirection element.
*/

static void		replace_redirection(t_acb *branch, int change_index, \
		char *content)
{
	char				*tag;
	char				*token;
	t_redirection_fd	*redirection;

	while (iter_pylst(branch->redirectionfd, (void **)&redirection))
	{
		tag = redirection->tagstokens->tags->value;
		token = redirection->tagstokens->tokens->value;
		if (ft_strequ(tag, "SUBAST") && ft_atoi(token) == change_index)
		{
			ft_memdel(&redirection->dest);
			redirection->dest = content;
			update_pylst(redirection->tagstokens->tags, 0, "STMT", 0, _ptr);
			update_pylst(redirection->tagstokens->tokens, 0, content, \
					NO_COPY_BUT_FREE, _chare);
		}
	}
}

/*
** replace_subast:
**
** Replace in a branch the content given by a subast with
** a CMDSUBT[123], QUOTE or DQUOTES.
** Try to replace this content in the tagstokens list of the branch,
** or replace in the filedescriptor list if it's not found.
*/

void			replace_subast(t_acb *branch, int change_index, char *content, \
		char *type_ast)
{
	size_t			index;
	char			*tag;
	char			*token;
	t_tagstokens	*tagstok;

	index = 0;
	tagstok = branch->tagstokens;
	while (index < tagstok->length)
	{
		tag = vindex_pylst(tagstok->tags, index);
		token = vindex_pylst(tagstok->tokens, index);
		if (ft_strequ(tag, "SUBAST") && ft_atoi(token) == change_index)
		{
			if (in(type_ast, "CMDSUBST1", "BRACEPARAM", NULL))
				substitution_insert(content, branch->tagstokens, index);
			else
			{
				update_pylst(tagstok->tokens, index, content, -1, _chare);
				update_pylst(tagstok->tags, index, "STMT", 0, _chare);
			}
			return ;
		}
		index++;
	}
	replace_redirection(branch, change_index, content);
}
