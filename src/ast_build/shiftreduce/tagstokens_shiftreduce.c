
# include "tmpsh.h"
# include "libft.h"
# include "globals.h"
# include "tokenizer.h"
# include "tagstokens.h"
# include "shiftreduce.h"


static t_bool find_error(t_tagstokens *tgtk, int i)
{
    tgtk->valid = FALSE;
    tgtk->token_error = ft_strdup(find_prev_token(tgtk, i, TRUE));
    return (TRUE);
}

static t_bool append_stack(t_tagstokens *tgtk, char *next_tag, size_t i)
{
    if (i < tgtk->length && ft_strequ(next_tag, "SPACES"))
        return (TRUE);
    else if (!tgtk->stack || revkeyinstack(tgtk->stack))
    {
        if (i < tgtk->length)
            push_pylst(&tgtk->stack, next_tag, 0, _ptr);
    }
    else if (find_error(tgtk, i))
    {
        return (FALSE);
    }
    return (TRUE);
}


void tagstokens_shiftreduce(t_tagstokens *tgtk)
{
    size_t i;
    int instack;
    t_bool forbidden;
    char *next_tag;

    i = 0;
    instack = TRUE;
    forbidden = check_forbidden_shiftreduce(tgtk->tags);
    while (i <= tgtk->length && forbidden)
    {
        if (!(forbidden = check_forbidden_shiftreduce(tgtk->tags)))
            break ;
        next_tag = (i < tgtk->length) ? get_value_pylst(tgtk->tags, i) : "";
        ft_printf("next_tag: %s | i: %d | instack: %d \n", next_tag, i, keyinstack(tgtk->stack, next_tag));
        print_pylst_chare(tgtk->stack);
        if ((instack = keyinstack(tgtk->stack, next_tag)) > -1)
        {
            ft_printf("YOLO\n");
            tgtk->stack = reduce_all(tgtk->stack, instack, next_tag);
        }
        else if (!(append_stack(tgtk, next_tag, i)) || !(++i))
            break ;
    }
    if (!forbidden)
        find_error(tgtk, --i);
    // maybe you need COMMAND_SH to be CMD...
    clear_stack_tagstokens(tgtk);
    if (tgtk->valid && len_pylst(tgtk->stack) > 0)
        tgtk->incomplete = TRUE;
}
