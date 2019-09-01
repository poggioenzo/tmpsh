#include "ttm.h"


/*
** is_redirection_ttm:
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



void	in_redirection_ttm(t_tags_tokens_monitor *self)
{
	t_bool		not_end;

	not_end = next_ttm(self, false);
	if (ft_strequ(self->tag, "SPACES"))
		not_end = next_ttm(self, false);
	if (not_end)
	{
		op_selector_ttm(self);
		self->begin_cmd = true;
	}
	else
	{
		self->tt->valid = false;
		self->tt->token_error = self->token;
	}
	self->begin_cmd = true;
}
