
#include "tagstokens.h"

static void insert_alias(t_pylst **here, t_pylst *alias, size_t i, t_bool deep)
{
    if (deep)
        replace_pylst(here, pylst_deepcpy(alias), i, i + 1);
    else
        replace_pylst(here, pylst_shacpy(alias), i, i + 1);
}


/*
** replace_alias_tagstokens:
**
** @self: actual tagstokens.
** @alias_input: input alias to transform.
** @i: index where insert alias tags and tokens.
**
** After tokenise and tag the result of the alias, the tokens will be insert
** at the index i with a deepcopy and tags with a shallowcopy.
*/


void replace_alias_tagstokens(t_tagstokens *self, char *alias_input, size_t i)
{
    t_tagstokens *tt_alias;

    input_init_tagstokens(&tt_alias, alias_input);
    insert_alias(&self->tokens, tt_alias->tokens, i, TRUE);
    insert_alias(&self->tags, tt_alias->tags, i, FALSE);
    self->valid = tt_alias->valid;
    update_length_tagstokens(self);
    free_tagstokens(&tt_alias, TRUE);
}
