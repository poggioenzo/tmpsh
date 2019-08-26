

#include "tagstokens.h"

char *str_command_tagstokens(t_tagstokens *self)
{
    size_t length;
    size_t i;
    char *tok;
    char *tag;
    char *str;

    length = 0;
    print_tagstokens(self);
    while (iter_tagstokens(self, &tok, &tag))
        length += ft_strlen(tok);
    str = ft_strnew(length);
    // if (str = ft_strnew(length) && length == 0)
    //     return (str);
    length = 0;
    while (iter_tagstokens(self, &tok, &tag))
    {
        if (!ft_strequ("SPACES", tag))
        {
            i = 0;
            ft_printf("%p\n", tok);
            while (tok[i])
            {
                str[length++] = tok[i++];
                ft_printf("%s\n", str);
            }
        }
        else
            str[length++] = ' ';
    }
    return(str);
}
