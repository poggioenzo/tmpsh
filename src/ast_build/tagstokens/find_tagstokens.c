#include "tagstokens.h"

/*
** find_prev_token:
**
** @self: actual tagstokens
** @i: index in the tagstokens
** @get_token: boolean to know if we wnat the token or the tag.
**
** Return the index of token if then tag is not SPACES else i - 1.
*/

int     find_prev_ind_token(t_tagstokens *self, int i)
{
    if (ft_strequ(get_value_pylst(self->tags, i),"SPACES") && i - 1 >= 0)
        i--;
    return (i);
}

/*
** find_next_ind_token:
**
** @self: actual tagstokens
** @i: index in the tagstokens
** @get_token: boolean to know if we wnat the token or the tag.
**
** Return the index of token if then tag is not SPACES else i + 1.
*/

int     find_next_ind_token(t_tagstokens *self, int i)
{
    if (ft_strequ(get_value_pylst(self->tags, i),"SPACES") &&\
                                                    i + 1 < (int)self->length)
        i++;
    return (i);
}

/*
** find_prev_token:
**
** @self: actual tagstokens
** @i: index in the tagstokens
** @get_token: boolean to know if we wnat the token or the tag.
**
** Return the string of token or tag according to get_token at the index i.
** If then tag is SPACES return the token or tag at the index i - 1.
*/

char    *find_prev_token(t_tagstokens *self, int i, t_bool get_token)
{
    if (ft_strequ(get_value_pylst(self->tags, i),"SPACES") && i - 1 >= 0)
        i--;
    return (get_token ? get_value_pylst(self->tokens, i) :\
                                            get_value_pylst(self->tags, i));
}

/*
** find_next_token:
**
** @self: actual tagstokens
** @i: index in the tagstokens
** @get_token: boolean to know if we wnat the token or the tag.
**
** Return the string of token or tag according to get_token at the index i.
** If then tag is SPACES return the token or tag at the index i + 1.
*/


char    *find_next_token(t_tagstokens *self, int i, t_bool get_token)
{

    if (ft_strequ(get_value_pylst(self->tags, i),"SPACES") &&\
                                                    i + 1 < (int)self->length)
        i++;
    return (get_token ? get_value_pylst(self->tokens, i) :\
                                            get_value_pylst(self->tags, i));
}
