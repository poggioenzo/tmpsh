#include "striplines_heredocs.h"


/*
** striplines_heredocs:
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

void	striplines_heredocs(t_heredocs *self)
{
	size_t		index;
	t_bool	new_line;
	char	*tag;
	char	*token;

	index = 0;
	new_line = true;
	while (index < self->tagstokens->length)
	{
		token = vindex_pylst(self->tagstokens->tokens, index);
		tag = vindex_pylst(self->tagstokens->tags, index);
		if (ft_strequ(tag, "NEW_LINE"))
			new_line = true;
		else if (ft_strequ(tag, "SPACES") && new_line)
		{
			//replace_first_tab seem to not exist.
			//Check allocation, set _ptr by default.
			//update_pylst(self->tagstokens->tokens, index, \
			//		replace_first_tab(token), 0, _ptr);
		}
		else
			new_line = false;
		index++;
	}
}
