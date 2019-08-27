#include "ast.h"

void    split_branch_ast(t_ast *self, t_tagstokens *tgtk)
{
    size_t i;
    size_t begin;
    char *and_or_begin;
    char *tag;

    i = 0;
    begin = 0;
    and_or_begin = "";
    while (i <= tgtk->length)
    {
        tag = (i < tgtk->length) ? get_value_pylst(tgtk->tags, i) : "" ;
        if (search_value(g_grammar->opening_tags, tag))
            i = skip_openning_tagstokens(tgtk, i, "\0") - 1;
        else if (in_pylst_chare(tag, \
                search_value(g_grammar->grammar,"ABS_TERMINATOR"))
                || (i == tgtk->length && begin != i))
        {
            push_pylst(&self->list_branch,
                init_acb(copy_tagstokens(tgtk, begin, i), and_or_begin, tag),
                0, _ptr);
            begin = i + 1;
            and_or_begin = "";
        }
        if (!(++i) || ft_strequ(tag, "CMDAND") || ft_strequ(tag, "CMDOR"))
            and_or_begin = tag;
    }
}
