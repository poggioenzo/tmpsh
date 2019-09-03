#include "libft.h"
#include "tmpsh.h"
#include "tagstokens.h"

/*
** prev_is_stmt:
**
** Check in the given tag list if the previous element is a STMT.
*/

static int		prev_is_stmt(t_pylst *tags, int index)
{
	char	*prev_tag;

	if (index >= 1)
	{
		prev_tag = vindex_pylst(tags, index - 1);
		return (ft_strequ(prev_tag, "STMT"));
	}
	return (0);
}

/*
** join_stmt:
**
** If a STMT is following an other STMT, concat them in a single token.
*/

void		join_stmt(t_acb *branch)
{
	size_t			index;
	t_tagstokens	*tagstok;
	char			*curr_tag;
	t_pylst			*prev_token;
	char			*new_stmt;

	tagstok = branch->tagstokens;
	index = 0;
	while (index < tagstok->length)
	{
		curr_tag = vindex_pylst(tagstok->tags, index);
		if (ft_strequ(curr_tag, "STMT") && prev_is_stmt(tagstok->tags, index))
		{
			prev_token = index_pylst(tagstok->tokens, index - 1);
			new_stmt = ft_strjoin(prev_token->value, prev_token->next->value);
			update_pylst(tagstok->tokens, index - 1, new_stmt, \
					NO_COPY_BUT_FREE, _chare);
			del_portion_pylst(&tagstok->tags, index, index + 1);
			del_portion_pylst(&tagstok->tokens, index, index + 1);
			update_length_tagstokens(tagstok);
			index--;
		}
		index++;
	}
}
