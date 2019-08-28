#include "init_ttm.h"


/*
** init_ttm:
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

void init_ttm(t_tagstokens *tagstokens)
{
	t_tags_tokens_monitor *self;

	self = (t_tags_tokens_monitor*)ft_memalloc(sizeof(t_tags_tokens_monitor));
	self->tt = tagstokens;
	self->i = -1;
	self->begin_cmd = TRUE;
	push_pylst(&self->opened, " ", 0, _ptr);
	check_ttm(self);
	free_pylst(self->heredocs_keys);
	free_pylst(self->opened);
	ft_memdel(&self);
}
