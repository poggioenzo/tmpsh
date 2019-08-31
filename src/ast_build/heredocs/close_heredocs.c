#include "heredocs.h"


/*
** close_heredocs:
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

void	close_heredocs(t_heredocs *self)
{
	//self->tagstokens = copytt(self, 0, -self->len_key);//Seem to not exist
	self->tagstokens->not_heredocs = false;
	if (self->minus)
		striplines(self);
	check_syntax_tagstokens(self->tagstokens); //Check if check_stack in python is check_syntax_tagstokens
	self->closed = true;
}
