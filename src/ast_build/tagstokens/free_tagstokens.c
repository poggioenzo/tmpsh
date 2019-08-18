#include "tagstokens.h"

/*
** free_tagstokens:
**
** @self: adress of tagstokens to free.
** @status: status to return
**
** Free tagstokens and its attributes if they exist.
*/


int free_tagstokens(t_tagstokens **self, int status)
{
    if (self && *self)
    {
        free_pylst(&(*self)->tokens, status);
        free_pylst(&(*self)->tags, status);
        free_pylst(&(*self)->stack, status);
        if ((*self)->token_error)
            ft_strdel(&(*self)->token_error);
        ft_memdel((void **)self);
    }
    return (status);
}
