#include <stdio.h>
#include "tmpsh.h"
#include "libft.h"
#include "globals.h"
#include "tokenizer_utils.h"
#include "tokenizer.h"

// typedef struct
// {
// 	t_pylst		*heredocs;
// 	t_pylst		*tokens;
// 	t_pylst		*tags;
// 	t_pylst		*stack;
// 	char		*token_error;
// 	t_bool		valid;
// 	t_bool		incomplete;
// 	int			length;
// }			t_tagstokens;


void init_tagstokens(t_tagstokens *self, t_pylst *tokens, t_pylst *tags)
{
  self = (t_tagstokens*)ft_memalloc(sizeof(t_tagstokens));
  self->tokens = tokens;
  self->tags = tags;
  self->stack = NULL; // t_pylst *
  self->token_error = NULL; // char *
  self->valid = TRUE;
  self->incomplete = FALSE;
  self->length = 0;
  self->iter = -1;
  // strip_tagstokens(self);
  // update_length(self);
}
