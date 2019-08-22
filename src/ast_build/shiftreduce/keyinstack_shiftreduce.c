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
    while (len_stack-- && !ret)
    {
        key = join_pylst(stack, " ");
        if (search_value(g_grammar->reverse, key))
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
    return (ft_strjoin(str, next_tag));
}


int     keyinstack(t_pylst *stack, char *next_tag)
{
    size_t  len_stack;
    char    *key;
    char    *extend_key;
    int     i;

    i = 0;
    extend_key = NULL;
    len_stack = len_pylst(stack);

    while (stack)
    {
        key = join_pylst(stack, " ");
        extend_key = get_extend_key(key, next_tag);
        if (search_value(g_grammar->grammar, key))
        {
            if (!search_value(g_grammar->grammar, extend_key))
                break ;
            return (i);
        }
        ft_strdel(&key);
        ft_strdel(&extend_key);
        i++;
        stack = stack->next;
    }
    return (-1);
}
