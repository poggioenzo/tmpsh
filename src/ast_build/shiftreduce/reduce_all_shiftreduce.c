# include "tmpsh.h"
# include "libft.h"
# include "globals.h"
# include "shiftreduce.h"

static t_pylst **reduce(t_pylst **stack, int instack)
{
    char *key;

    key = join_pylst(index_pylst(*stack, instack), " ");
    del_portion_pylst(stack, instack, len_pylst(*stack));
    push_pylst(stack, search_value(g_grammar->reverse, key) , 0, _ptr);
    ft_strdel(&key);
    return stack;

}

t_pylst *reduce_all(t_pylst **stack, int instack, char *next_tag)
{
    while (instack > -1)
    {
        stack = reduce(stack, instack);
        instack = keyinstack(*stack, next_tag);
    }
    return (*stack);
}
