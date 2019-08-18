
#include "tagstokens.h"

/*
** clear_stack_tagstokens:
**
** @self: actual tagstokens.
**
** Remove all CMD string from self->stack.
*/

void clear_stack_tagstokens(t_tagstokens *self)
{
    char *str;
    int *to_delete;
    int n;
    int i;

    n = 0;
    i = 0;
    to_delete = (int *)ft_memalloc((len_pylst(self->stack) + 1) * sizeof(int));
    while (pylst_iter(self->stack, (void **)&str))
    {
        if (ft_strequ(str, "CMD"))
            to_delete[n++] = i;
        i++;
    }
    while (n--)
        del_portion_pylst(&self->stack, to_delete[n], to_delete[n]+1);
    ft_memdel((void **)&to_delete);
}
