#include "redirectionfd.h"


/*
** str_redfd:
**
** description:
** Create and return string repredentation of a redirection fd.
**
** parameter:
** - (t_redirection_fd *) self : the actual redirection fd.
**
** return value:
** - (char *) str : string repredentation of redirection fd.
*/


char *str_redfd(t_redirection_fd    *self)
{
    char *str;

    str = ft_strnew(0);
    str = free_join(str, GREEN, FALSE);
    str = free_join(str, self->type, FALSE);
    str = free_join(str, WHITE" ", FALSE);
    str = free_join(str, str_command_tagstokens(self->tagstokens), TRUE);
    str = free_join(str, " source:", FALSE);
    str = free_join(str, ft_itoa(self->source), TRUE);
    str = free_join(str, " | ", FALSE);
    return (str);
}
