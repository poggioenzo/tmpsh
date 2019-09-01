#include "ttm.h"


/*
** next_ttm:
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

t_bool next_ttm(t_tags_tokens_monitor *self, t_bool clear)
{
	t_bool ret;

	self->i++;
	ret = self->i < (int)self->tt->length;
	if (ret)
	{
		self->tag = vindex_pylst(self->tt->tags, self->i);
		self->tag = vindex_pylst(self->tt->tags, self->i);
		if (clear)
			self->i = delitems_tagstokens(self->tt, self->i, self->i + 1, self->i - 1);
	}
	return (ret);
}
