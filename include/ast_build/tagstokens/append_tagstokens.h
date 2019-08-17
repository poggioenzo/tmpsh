#ifndef APPEND_TAGSTOKENS_H
# define APPEND_TAGSTOKENS_H

void append_tagstokens(t_tagstokens *self, char *token, char *tag);
void append_token_tagstokens(t_tagstokens *self, char *token);
void append_tag_tagstokens(t_tagstokens *self, char *tag);
void stack_append_tagstokens(t_tagstokens *self, char *tag);

#endif
