# include "tmpsh.h"
# include "libft.h"
# include "globals.h"
# include "tokenizer_utils.h"

t_bool revkeyinstack(t_pylst *stack)
{
    size_t  len_stack;
    char    *key;
    t_bool  ret;

    ret = FALSE;
    len_stack = len_pylst(stack);
    while (--len_stack > -1 && !ret)
    {
        key = join_pylst(stack, " ");
        if (ops_begin_with(key ,g_grammar->reverse))
            ret = TRUE;
        ft_strdel(&key);
    }
    return ret;
}

static char *get_extend_key(char *key, char *next_tag)
{

    char *str;

    str = "";
    if (key)
    {
        str = ft_strjoin(key, " ");
        ft_strdel(&key);
    }
    return (ft_strjoin(str, next_tag))
}


int     keyinstack(t_pylst *stack, char *next_tag)
{
    size_t  len_stack;
    char    *key;
    char    *extend_key;
    int     i;
    t_pylst *cp_stack;

    i = 0;
    extend_key = NULL;
    // iterator pylst
    while ((size_t) i < len_stack)
    {
        cp_stack = NULL;
        key = join_pylst();
        free_pylst(cp_stack);
        extend_key = get_extend_key(key, next_tag);
        if (search_value(g_grammar->grammar, key))
        {
            if (search_value(g_grammar->grammar, extend_key))
                break ;
            return (i);
        }
        ft_strdel(&key);
        ft_strdel(&extend_key);
        i++;
    }
    return (-1);
}
