
# include "tmpsh.h"
# include "libft.h"
# include "globals.h"
# include "tokenizer.h"
# include "tagstokens.h"

static t_bool cond_check_forbidden_shiftreduce(char *key, int i, t_pylst *instack, t_pylst *tags)
{
    int index_forbidden;
    char **str_forbidden;

    if (ft_strequ("FORBIDDEN", search_value(g_grammar->reverse, key)))
    {
        index_forbidden = len_pylst(instack);
        str_forbidden = (char **)&get_value_pylst(tags, index_forbidden);
        if (ft_strequ("SPACES", *str_forbidden))
            str_forbidden = (char **)&get_value_pylst(tags, --index_forbidden);
        *str_forbidden = "FORBIDDEN";
        return (TRUE);
    }
    return (FALSE);
}

int check_forbidden_shiftreduce(pylst *tags)
{
    int i;
    int len_tags;
    int spaces;
    t_pylst *instack;
    char *key;

    i = 0;
    spaces = 0;
    len_tags = len_pylst(tags);
    while (i < )
    {
        key = join_pylst(instack, " ");
        if (cond_check_forbidden_shiftreduce(key, i, instack, tags))
            return FALSE;
        ft_strdel(&key);
    }

}


void shiftreduce(t_tagstokens *tgtk)
{
    int i;
    t_bool instack;
    int forbidden;
    char *next_tag;



}
