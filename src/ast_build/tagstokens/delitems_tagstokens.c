
#include "tagstokens.h"


int		delitems_tagstokens(t_tagstokens *self, int start, int stop, int status)
{
	del_portion_pylst(&self->tokens, start, stop);
	del_portion_pylst(&self->tags, start, stop);
	update_length_tagstokens(self);
	return (status);
}
