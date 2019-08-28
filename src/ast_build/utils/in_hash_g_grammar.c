
#include "utils.h"

t_bool in_grammar(char *tag, char *key)
{
    return (in_pylst_chare(tag, search_value(g_grammar->grammar, key)));
}

t_bool in_reverse(char *tag, char *key)
{
    return (in_pylst_chare(tag, search_value(g_grammar->reverse, key)));
}

t_bool in_opening_tags(char *tag, char *key)
{
    return (in_pylst_chare(tag, search_value(g_grammar->opening_tags, key)));
}

t_bool in_dquotes_opening_tags(char *tag, char *key)
{
    return (in_pylst_chare(tag, search_value(
                                    g_grammar->dquotes_opening_tags, key)));
}
