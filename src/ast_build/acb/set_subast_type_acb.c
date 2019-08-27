#include "set_subast_type_acb.h"


/*
** set_subast_type_acb:
**
** description:
** Update all type of the subast of this branch.
**
** parameter:
** - (t_acb *) self : Actual abstract command branch.
*/

void    set_subast_type_acb(t_acb *self)
{
    t_ast   *current;
    char    *value;
    int     i;

    i = 0;
    while (pylst_iter(self->subcmd_type, (void **)&value))
    {
        current = get_value_pylst(self->subast, i++);
        current->type = value;
    }
}
