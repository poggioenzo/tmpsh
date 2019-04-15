#include "t_operand_utils.h"
#include "newline_keypress.h"
#include <stdlib.h>

/*
** get_last_bracket:
**
** From a given t_operand list, search the last opening bracket element,
** which are not a seperator.
*/

t_operand	*get_last_bracket(t_operand *operand_list)
{
	t_operand *last_open;

	last_open = NULL;
	while (operand_list)
	{
		if (!(operand_list->type & SEPARATOR))
				last_open = operand_list;
		operand_list = operand_list->next;
	}
	return (last_open);
}

