#include "heredocs.h"


/*
** add_tags_tokens_heredocs:
**
** description:
** describe what you function do.
**
** parameter:
** - (type) name : what is this param?
**
** return value:
** - (type) value : descibe output.
*/

void	add_tags_tokens_heredocs(t_heredocs *self, char *tag, char *token)
{
	char	*tmp_tag;

	if (self->quoted)
		tag = "STMT";
	else if (!self->in_cmdsubst)
	{
		if ((tmp_tag = search_value(g_grammar->dquotes_opening_tags, tag)))
		{
			self->in_cmdsubst = true;
			push_pylst(&self->stack, tmp_tag, 0, _ptr);
		}
		else
			tag = in(tag, "VAR", "STMT", "SPACES", "NEW_LINE", NULL) ?\
				  tag : "STMT";
	}
	else
		check_stack_heredocs(self, tag);
	append_tagstokens(self->tagstokens, tag, token);
}
