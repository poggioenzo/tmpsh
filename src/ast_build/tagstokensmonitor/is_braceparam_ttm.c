#include "ttm.h"


/*
** is_braceparam_ttm:
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

void	is_braceparam_ttm(t_tags_tokens_monitor *self)
{
	t_bool	not_end;
	char	*stmt_tag;

	not_end = next_ttm(self, false);
	stmt_tag = self->tag;
	not_end = not_end && next_ttm(self, false);
	if (!ft_strequ(stmt_tag, "STMT") || !ft_strequ(self->tag, "END_BRACE"))
	{
		if (not_end)
		{
			self->tt->valid = false;
			self->tt->token_error = "bad substitution";
		}
	}
}
