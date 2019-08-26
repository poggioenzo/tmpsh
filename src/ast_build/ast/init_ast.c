

#include "ast.h"

// typedef struct
// {
// 	t_tagstokens	*tagstokens;
// 	char			*begin_andor;
// 	char			*tag_end;
// 	t_pylst			*subast;
// 	t_pylst			*subcmd_type;
// 	t_pylst			*redirectionfd;
// 	char			*command;
// 	int				stdin;
// 	int				stdout;
// 	t_bool			background;
// 	int				status;
// 	pid_t			pid;
// 	pid_t			pgid;
// 	t_bool			complete;
// }			t_acb;

char *split_shift(char **str)
{
    char **splitted;
    char **actual;
    char *shifted;
    char *tmp;

    shifted = ft_strnew(0);
    splitted = ft_strsplit(*str, "\n");
    actual = splitted;
    tmp = "\t";
    while (*actual)
    {
        *actual = ft_fstrjoin(&tmp, actual, FALSE, TRUE);
        actual++;
    }
    tmp = "\n";
    actual = splitted;
    while (*splitted)
    {
        *splitted = ft_fstrjoin(splitted, &tmp, TRUE, FALSE);
        shifted = ft_fstrjoin(&shifted, splitted++, TRUE, TRUE);
    }
    ft_memdel((void **)actual);
    ft_strdel(str);
    return (shifted);
}

char *str_ast(t_ast *self);


char *str_acb(t_acb *self)
{
    DF;
    char *str;
    char *str_subast;
    t_ast *value;

    str = ft_strnew(0);
    str_subast = ft_strnew(0);
    ft_printf("LOL\n");
    str = free_join(str, BLUE, FALSE);
    str = free_join(str, self->begin_andor ? self->begin_andor : "", FALSE);
    str = free_join(str, WHITE, FALSE);
    ft_printf("LOL\n");
    str = free_join(str, self->print ? self->print : "", FALSE);
    ft_printf("LOL\n");
    str = free_join(str, RED, FALSE);
    str = free_join(str, self->tag_end ? self->tag_end : "", FALSE);
    ft_printf("LOL\n");
    str = free_join(str, GREEN, FALSE);
    // while (pylst_iter(self->redirectionfd, &value))
    //     str = free_join(&str, value->print, FALSE);
    str = free_join(str, WHITE, FALSE);
    str = free_join(str, "\n", FALSE);
    ft_printf("LOL\n");
    while (pylst_iter(self->subast, (void **)&value))
        str_subast = free_join(str_subast, str_ast(value), FALSE);
    str_subast = split_shift(&str_subast);
    ft_printf("LOL\n");
    str = free_join(str, str_subast, TRUE);
    DFE;
    return (str);

}

char *str_ast(t_ast *self)
{
    DFB;
    char *str;
    char *string_acb;
    t_acb *value;

    str = ft_strnew(0);
    string_acb = ft_strnew(0);
    str = free_join(str, YELLOW, FALSE);
    ft_printf("LOL\n");
    str = free_join(str, self->type ? self->type : "NONE", FALSE);
    str = free_join(str, "\n  ", FALSE);
    str = free_join(str, WHITE, FALSE);
    ft_printf("LOL\n");
    while (pylst_iter(self->list_branch, (void **)&value))
    {
        ft_printf("LOL\n");
        string_acb = free_join(string_acb, str_acb(value), TRUE);
    }
    ft_printf("LOL\n");
    string_acb = split_shift(&string_acb);
    str = free_join(str, string_acb, TRUE);
    DFT;
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


void check_subast(t_acb *self)
{
    size_t i;
    size_t begin;
    char *tag;

    i = 0;
    while (i < self->tagstokens->length)
    {
        tag = get_value_pylst(self->tagstokens->tags, i);
        ft_printf( GREEN"%s"WHITE, tag);
        if (search_value(g_grammar->opening_tags, tag))
        {
            ft_printf( RED"\n%s"WHITE, tag);
            begin = i + 1;
            push_pylst(&self->subcmd_type, tag, 0, _ptr);
            i = skip_openning_tagstokens(self->tagstokens, i, NULL) - 1;
            push_pylst(&self->subast, copy_tagstokens(self->tagstokens,
                 begin, i), 0, _ptr);
            replace_subast(self->tagstokens, begin - 1, i + 1, \
                len_pylst(self->subast) - 1);
            i = begin - 1;
        }
        ft_printf("\n");
        i++;
    }
}


t_acb    *init_acb(t_tagstokens *tgtk, char *begin_andor, char *tag_end)
{
    t_acb *self;

    self = (t_acb*)ft_memalloc(sizeof(t_acb));
    self->tagstokens = tgtk;
    self->begin_andor = begin_andor;
    self->tag_end = "";
    if (in_pylst_chare(tag_end, search_value(g_grammar->grammar,"ABS_TERMINATOR")))
        self->tag_end = tag_end;
    self->subast = NULL;
    self->subcmd_type = NULL;
    self->redirectionfd = NULL;
    self->command = str_command_tagstokens(tgtk);
    self->stdin = -1;
    self->stdout = -1;
    self->background = FALSE;
    self->status = -1;
    self->pid = -1;
    self->pgid = 0;
    self->complete = FALSE;
    strip_tagstokens(tgtk);
    check_subast(self);
    self->print = str_command_tagstokens(tgtk);
    ft_printf("%s\n", self->print);
    // self.set_subast_type()
    // self.check_redirection()
    return (self);
}

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
    // self->print = str_command_tagstokens(tgtk);
    // ft_printf("%s\n", self->print);
    return (self);
}
