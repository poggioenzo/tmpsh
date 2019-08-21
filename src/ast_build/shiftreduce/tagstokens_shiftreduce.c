
# include "tmpsh.h"
# include "libft.h"
# include "globals.h"
# include "tokenizer.h"
# include "tagstokens.h"
# include "shiftreduce.h"


// static void

void tagstokens_shiftreduce(t_tagstokens *tgtk)
{
    size_t i;
    t_bool instack;
    t_bool forbidden;
    char *next_tag;

    i = 0;
    instack = TRUE;
    next_tag = NULL;
    forbidden = check_forbidden_shiftreduce(tgtk->tags);
    while (i < tgtk->length && forbidden)
    {
        i++;
    }

}
