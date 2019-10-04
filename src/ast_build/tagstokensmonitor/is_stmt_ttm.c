

#include "ttm.h"

// def remove_escape_token(self):
//     if self.token and self.token[0] == gv.GRAMMAR.escape:
//         self.tt.tokens[self.i] = self.token[1:]
//
// def is_stmt(self):
//     self.begin_cmd = self.check_aliases()
//     self.remove_escape_token()


void remove_escape_token_ttm(t_tags_tokens_monitor *self)
{
  if (self->token && self->token[0] == g_grammar->escape)
    ft_strcpy(self->token, self->token + 1);
}

void is_stmt_ttm(t_tags_tokens_monitor *self)
{
  self->begin_cmd = check_aliases_ttm(self);
  remove_escape_token_ttm(self);
}
