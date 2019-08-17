
#include "tagstokens.h"

void	strip_tagstokens(t_tagstokens *self)
{
	if (self->length > 0 && \
		ft_strequ((char *)get_value_pylst(self->tags, 0), "SPACES"))
		delitems_tagstokens(self, 0, 1, TRUE);
	if (self->length > 0 && \
		ft_strequ((char *)get_value_pylst(self->tags, -1), "SPACES"))
		delitems_tagstokens(self, -1, self->length, TRUE);
	if (self->length == 1 && \
		ft_strequ((char *)get_value_pylst(self->tags, 0), "SPACES"))
	{
		free_pylst(&self->tags, 42);
		free_pylst(&self->tokens, 42);
	}
}
