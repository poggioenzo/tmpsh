

#include "ast.h"




char *str_acb(t_acb *self)
{
    char *str;
    char *str_subast;
    t_ast *value;

    str = ft_strnew(0);
    str_subast = ft_strnew(0);
    str = free_join(str, BLUE"__", FALSE);
    str = free_join(str, self->begin_andor ? self->begin_andor : "", FALSE);
    str = free_join(str, "__ "WHITE, FALSE);
    str = free_join(str, self->print ? self->print : "", FALSE);
    str = free_join(str, RED" __", FALSE);
    str = free_join(str, self->tag_end ? self->tag_end : "", FALSE);
    str = free_join(str, "__ ", FALSE);
    while (pylst_iter(self->redirectionfd, (void**)&value))
         str = free_join(str, value->print, FALSE);
    str = free_join(str, WHITE, FALSE);
    str = free_join(str, "\n", FALSE);
    while (pylst_iter(self->subast, (void **)&value))
        str_subast = free_join(str_subast, str_ast(value), FALSE);
    str_subast = split_shift(&str_subast);
    str = free_join(str, str_subast, TRUE);
    return (str);

}

char *str_ast(t_ast *self)
{
    char *str;
    char *string_acb;
    t_acb *value;

    str = ft_strnew(0);
    string_acb = ft_strnew(0);
    str = free_join(str, YELLOW, FALSE);
    str = free_join(str, self->type ? self->type : "NONE", FALSE);
    str = free_join(str, "\n  ", FALSE);
    str = free_join(str, WHITE, FALSE);
    while (pylst_iter(self->list_branch, (void **)&value))
        string_acb = free_join(string_acb, str_acb(value), TRUE);
    string_acb = split_shift(&string_acb);
    str = free_join(str, string_acb, TRUE);
    return (str);
}



static void     replace_subast(t_tagstokens *tgtk, size_t begin, size_t end, int number)
{
    t_pylst *tag;
    t_pylst *token;
    char    *str;

    tag = NULL;
    token = NULL;
    str = ft_itoa(number);
    push_pylst(&tag, "SUBAST", 0, _ptr);
    push_pylst(&token, str, ft_strlen(str), _chare);
    replace_pylst(&tgtk->tags, tag, begin, end);
    replace_pylst(&tgtk->tokens, token, begin, end);
    update_length_tagstokens(tgtk);
}


void check_subast_acb(t_acb *self)
{
    size_t i;
    size_t begin;
    char *tag;

    i = 0;
    while (i < self->tagstokens->length)
    {
        tag = get_value_pylst(self->tagstokens->tags, i);
        if (search_value(g_grammar->opening_tags, tag))
        {
            begin = i + 1;
            push_pylst(&self->subcmd_type, tag, 0, _ptr);
            i = skip_openning_tagstokens(self->tagstokens, i, NULL) - 1;
            push_pylst(&self->subast, init_ast(copy_tagstokens(self->tagstokens,
                 begin, i)), 0, _ptr);
            replace_subast(self->tagstokens, begin - 1, i + 1, \
                len_pylst(self->subast) - 1);
            i = begin - 1;
        }
        i++;
    }
}

void    set_subast_type_acb(t_acb *self)
{
    t_ast   *current;
    char    *value;
    int     i;

    i = 0;
    while (pylst_iter(self->subcmd_type, (void **)&value))
    {
        current = get_value_pylst(self->subast, i++);
        current->type = value;
    }
}




t_ast	*init_ast(t_tagstokens *tgtk)
{
    t_ast *self;

    self = (t_ast*)ft_memalloc(sizeof(t_ast));
    self->list_branch = NULL;
    self->type = "ROOT";
    self->link_fd = 0;
    self->pid = -1;
    self->command = str_command_tagstokens(tgtk);
    self->complete = FALSE;
    split_branch_ast(self, tgtk);
    update_length_tagstokens(tgtk);
    return (self);
}


char *str_redfd(t_redirection_fd    *self)
{
    char *str;

    str = ft_strnew(0);
    str = free_join(str, GREEN, FALSE);
    str = free_join(str, self->type, FALSE);
    str = free_join(str, WHITE" ", FALSE);
    str = free_join(str, str_command_tagstokens(self->tagstokens), TRUE);
    str = free_join(str, " source:", FALSE);
    str = free_join(str, ft_itoa(self->source), TRUE);
    str = free_join(str, " | ", FALSE);
    return (str);
}


t_redirection_fd    *init_redfd(t_tagstokens *tgtk, char *type,\
     char *source)
{
    t_redirection_fd    *self;

    self = (t_redirection_fd*)ft_memalloc(sizeof(t_redirection_fd));
    self->tagstokens = tgtk;
    self->type = type;
    self->heredoc_ast = NULL;
    if (!source)
        source = (ft_strequ(self->type, "READ_FROM_FD")\
        || ft_strequ(self->type, "READ_FROM")) ?  "0" : "1" ;
    self->source = ft_atoi(source);
    self->dest = get_value_pylst(self->tagstokens->tokens,\
        self->tagstokens->length - 1);
    self->close = (ft_strequ(self->type, "READ_FROM_FD")\
        || ft_strequ(self->type, "TRUNC_TO_FD")) && ft_strequ(self->dest, "-");
    self->error = FALSE;
    if ((ft_strequ(self->type, "HEREDOCMINUS") \
        || ft_strequ(self->type, "HEREDOC")))
        ;// get_heredoc_ast(self);
    self->print = str_redfd(self);
    return (self);
}
