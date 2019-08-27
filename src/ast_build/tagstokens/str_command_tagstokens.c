

#include "tagstokens.h"

char *str_command_tagstokens(t_tagstokens *self)
{
    char *tok;
    char *tag;
    char *str;

    str = ft_strnew(0);
    while (iter_tagstokens(self, &tok, &tag))
    {
        if (ft_strequ("SPACES", tag))
            str = free_join(str, " ", FALSE);
        else if (ft_strequ("SUBAST", tag))
        {
            str = free_join(str, YELLOW, FALSE);
            str = free_join(str, tok, FALSE);
            str = free_join(str, WHITE, FALSE);
        }
        else
            str = free_join(str, tok, FALSE);
    }
    return(str);
}
