# include "tmpsh.h"
# include "libft.h"
# include "globals.h"
# include "tokenizer_utils.h"

t_bool revkeyinstack(t_pylst *stack)
{
    size_t  len_stack;
    char    *key;
    t_bool  ret;
    t_pylst *cpstack;

    ret = FALSE;
    len_stack = len_pylst(stack);
    while (len_stack--  && !ret)
    {
        cpstack = slice_pylst(stack, len_stack, len_pylst(stack));
        key = join_pylst(cpstack, " ");
        if (ops_begin_with(key, g_grammar->reverse_list))
        {
            ret = TRUE;
            free_pylst(&cpstack, ft_strdel_out(&key, 0));
            break;
        }
        free_pylst(&cpstack, ft_strdel_out(&key, 0));
    }
    return ret;
}

static char *get_ext_key(char *key, char *next_tag)
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
    char    *ext_key;
    int     i;

    i = 0;
    len_stack = len_pylst(stack);
    while (stack)
    {
        key = join_pylst(stack, " ");
        ext_key = get_ext_key(ft_strdup(key), next_tag);
        if (search_value(g_grammar->reverse, key))
        {
            if (search_value(g_grammar->reverse, ext_key))
                break ;
            return (i);
        }
        ft_strdel_out(&ext_key, ft_strdel_out(&key, 0));
        i++;
        stack = stack->next;
    }
    return (-1);
}
