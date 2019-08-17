#include "tagstokens.h"

void	update_length_tagstokens(t_tagstokens *self)
{
	self->length = len_pylst(self->tokens);
}
