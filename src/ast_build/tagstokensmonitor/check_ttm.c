#include "ttm.h"


/*
** check_ttm:
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

void check_ttm(t_tags_tokens_monitor *self)
{
	while (next_ttm(self))
		op_selector_ttm(self);
}
