#include "ttm.h"


/*
** reset_ttm:
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

void reset_ttm(t_tags_tokens_monitor *self)
{
	self->begin_cmd = TRUE;
	free_pylst(&g_passed_alias, 42);
}
