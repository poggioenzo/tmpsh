

#include "ast.h"


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
