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
    t_pylst *cpstack;

    i = 0;
    len_stack = len_pylst(stack);
    while (stack)
    {
        cpstack = slice_pylst(stack, i, len_stack);
        key = join_pylst(cpstack, " ");
        ext_key = get_ext_key(key, next_tag);
        ft_printf("%s \n",key);
        ft_printf("%s \n",ext_key);
        ft_printf("%p \n",search_value(g_grammar->grammar, key));
        if (search_value(g_grammar->grammar, key))
        {
            ft_printf("%p \n",search_value(g_grammar->grammar, ext_key));
            if (search_value(g_grammar->grammar, ext_key))
                break ;
            return (i);
        }
        free_pylst(&cpstack, ft_strdel_out(&ext_key, ft_strdel_out(&key, 0)));
        i++;
        stack = stack->next;
    }
    return (-1);
}
