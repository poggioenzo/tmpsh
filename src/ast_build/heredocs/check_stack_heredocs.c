#include "heredocs.h"

/*
** check_stack_heredocs:
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

void	check_stack_heredocs(t_heredocs *self, char *tag)
{
	char		*last_stack;
	char		*tmp_tag;

	last_stack = vindex_pylst(self->stack, -1);
	if (ft_strequ(tag, last_stack))
	{
		pop_pylst(&self->stack, -1);
		if (len_pylst(self->stack) == 0)
			self->in_cmdsubst = false;
	}
	else if (ft_strequ(tag, "QUOTE") && !ft_strequ(last_stack, "DQUOTES"))
		push_pylst(&self->stack, tag, 0, _ptr);
	else if (ft_strequ(tag, "DQUOTES") && !ft_strequ(last_stack, "QUOTE"))
		push_pylst(&self->stack, tag, 0, _ptr);
	else if (search_value(g_grammar->opening_tags, tag) && \
			!ft_strequ(last_stack, "QUOTE"))
	{
		if (ft_strequ(last_stack, "DQUOTES") && \
				(tmp_tag = search_value(g_grammar->dquotes_opening_tags, tag)))
			push_pylst(&self->stack, tmp_tag, 0, _ptr);
		else
		{
			tmp_tag = search_value(g_grammar->opening_tags, tag);
			push_pylst(&self->stack, tmp_tag, 0, _ptr);
		}
	}
}
