#include "tmpsh.h"

/*
** split_shift:
**
** description:
** Split a string on \n and add \t before each strings splited then
** join all strings with \n. And free the inputed string.
**
** parameter:
** - (char**) str : the string to modify.
**
** return value:
** - (char *) value : splited shifted and joined string.
*/

char *split_shift(char **str)
{
    char **splitted;
    char **actual;
    char *shifted;
    char *tmp;

    shifted = ft_strnew(0);
    splitted = ft_strsplit(*str, "\n");
    actual = splitted;
    tmp = "\t";
    while (*actual)
    {
        *actual = ft_fstrjoin(&tmp, actual, FALSE, TRUE);
        actual++;
    }
    tmp = "\n";
    actual = splitted;
    while (*splitted)
    {
        *splitted = ft_fstrjoin(splitted, &tmp, TRUE, FALSE);
        shifted = ft_fstrjoin(&shifted, splitted++, TRUE, TRUE);
    }
    ft_memdel((void **)actual);
    ft_strdel(str);
    return (shifted);
}
