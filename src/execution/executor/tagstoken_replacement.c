#include "tmpsh.h"
#include "libft.h"

/*
** replace_redirection:
**
** If the replacement is not done in the branch tagstokens,
** search if the replacement can be done inside a redirection element.
*/

static void		replace_redirection(t_acb *branch, int change_index, char *content)
{
	char				*tag;
	char				*token;
	t_redirection_fd	*redirection;
	while (iter_pylst(branch->redirectionfd, (void **)&redirection))
	{
		tag = (char *)redirection->tagstokens->tags->value;
		token = (char *)redirection->tagstokens->tokens->value;
		if (ft_strequ(tag, "SUBAST") && ft_atoi(token) == change_index)
			redirection->dest = content;
	}
}

/*
** replace_subast:
**
** Replace in a branch the content given by a subast with
** a CMDSUBT[123].
** Try to replace this content in the tagstokens list of the branch,
** or replace in the filedescriptor list if it's not found.
*/

void			replace_subast(t_acb *branch, int change_index, char *content)
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
