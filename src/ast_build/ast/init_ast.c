

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

static void     replace_subast(t_tagstokens *tgtk, size_t begin, size_t end, int number)
{
    DF;
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
    DF;
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
            push_pylst(&self->subast, copy_tagstokens(self->tagstokens,
                 begin, i), 0, _ptr);
            replace_subast(self->tagstokens, begin - 1, i + 1, \
                len_pylst(self->subast) - 1);
            i = begin - 1;
        }
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
    self->command = NULL;
    self->stdin = -1;
    self->stdout = -1;
    self->background = FALSE;
    self->status = -1;
    self->pid = -1;
    self->pgid = 0;
    self->complete = FALSE;
    strip_tagstokens(tgtk);
    print_tagstokens(tgtk);
    check_subast(self);
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
    self->command = NULL;
    self->complete = FALSE;
    split_branch_ast(self, tgtk);
    return (self);
}
