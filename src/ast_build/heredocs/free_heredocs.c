#include "heredocs.h"


/*
** free_heredocs:
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

int			free_heredocs(t_heredocs **self, int status)
{
	ft_strdel(&(*self)->key);
	free_tagstokens(&(*self)->tagstokens, status);
	ft_memdel((void **)self);
	return (status);
}
