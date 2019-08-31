#include "ttm.h"


/*
** is_heredocs_ttm:
**
** description:
** describe what you function do.
**
** parameter:
** - (type) name : what is this param?
**
** return value:
** - (type) value : descibe output.
*/

static char *get_end_tag(char *tag)
{
	if (in_grammar(tag, "QUOTES"))
		return (tag);
	return ("NEW_LINE");
}


static char *transform_end_tag(char *tag)
{
	if (ft_strequ(tag, "QUOTE"))
		tag = "END_QUOTE";
	if (ft_strequ(tag, "DQUOTES"))
		tag = "END_DQUOTES";
	return (tag);
}


static void append_to_heredocs_keys(t_tags_tokens_monitor *self, char *key,
									int len , t_bool minus)
{
	t_pylst *list_param;

	push_pylst(&list_param, key, (ft_strlen(key) + 1) * sizeof(char), _chare);
	push_pylst(&list_param, &len, sizeof(int), _inte);
	push_pylst(&list_param, &minus, sizeof(int), _inte);
	push_pylst(&self->heredocs_keys, list_param, 0, _ptr);
}


void is_heredocs_ttm(t_tags_tokens_monitor *self)
{
	t_bool minus;
	t_bool not_end;
	t_pylst *list_tok;
	int j;

	if (ft_strequ(self->tag, "SPACES"))
		not_end = next_ttm(self, false);
	if (not_end)
	{
		if (search_value(g_grammar->opening_tags, self->tag))
		{
			j = skip_openning_tagstokens(self->tt, self->i,
										get_end_tag(self->tag));
			list_tok = slice_pylst(self->tt->tokens, self->i, j);
			self->i = j - 1;
			self->tag = transform_end_tag(self->tag);
			append_to_heredocs_keys(self, join_pylst(list_tok, ""),
												 len_pylst(list_tok), minus);
			free_pylst(&list_tok, 42);
		}
		else
			append_to_heredocs_keys(self, self->token, 1, minus);
	}
	else
	{
		self->tt->valid = false;
		self->tt->token_error = ft_strdup(self->token);
	}
	self->begin_cmd = true;
}
