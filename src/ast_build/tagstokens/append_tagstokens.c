
#include "tagstokens.h"

static void _append_tag(t_pylst *tag_stack, char *tag)
{
    push_pylst(&tag_stack, tag, 0, _ptr);
}

void stack_append_tagstokens(t_tagstokens *self, char *tag)
{
    _append_tag(self->stack ,tag);
}

void append_tag_tagstokens(t_tagstokens *self, char *tag)
{
    _append_tag(self->tags ,tag);
}

void append_token_tagstokens(t_tagstokens *self, char *token)
{
    push_pylst(&(self->tokens), ft_strdup(token), ft_strlen(token) + 1 *\
            sizeof(char) , _chare);
}

/*
** init_tagstokens:
**
** Params:
** @self: actual tagstokens.
** @token: string of the token to append.
** @tag: string of the tag to append.
**
** Append respectively tag and token to pylst self->tags and self->tokens.
** Update self->length.
*/

void append_tagstokens(t_tagstokens *self, char *token, char *tag)
{
    append_tag_tagstokens(self, tag);
    append_token_tagstokens(self, token);
    self->length++;
}
