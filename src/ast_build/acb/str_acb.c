#include "str_acb.h"

/*
** str_acb:
**
** description:
** Create and return string repredentation of an acb.
**
** parameter:
** - (t_acb *) self : the actual abstract command branch.
**
** return value:
** - (char *) str : string repredentation of an acb.
*/

char *str_acb(t_acb *self)
{
    char *str;
    char *str_subast;
    t_ast *value;

    str = ft_strnew(0);
    str_subast = ft_strnew(0);
    str = free_join(str, BLUE"__", FALSE);
    str = free_join(str, self->begin_andor ? self->begin_andor : "", FALSE);
    str = free_join(str, "__ "WHITE, FALSE);
    str = free_join(str, self->print ? self->print : "", FALSE);
    str = free_join(str, RED" __", FALSE);
    str = free_join(str, self->tag_end ? self->tag_end : "", FALSE);
    str = free_join(str, "__ ", FALSE);
    while (pylst_iter(self->redirectionfd, (void**)&value))
         str = free_join(str, value->print, FALSE);
    str = free_join(str, WHITE, FALSE);
    str = free_join(str, "\n", FALSE);
    while (pylst_iter(self->subast, (void **)&value))
        str_subast = free_join(str_subast, str_ast(value), FALSE);
    str_subast = split_shift(&str_subast);
    str = free_join(str, str_subast, TRUE);
    return (str);
}
