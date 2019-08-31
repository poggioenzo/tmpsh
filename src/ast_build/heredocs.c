#include "tmpsh.h"
#include "libft.h"
#include "tagstokens.h"
#include "check_syntax_tagstokens.h"

int			free_heredocs(t_heredocs **self, int status)
{
	ft_strdel(&(*self)->key);
	free_tagstokens(&(*self)->tagstokens, status);
	ft_memdel((void **)self);
	return (status);
}

void	init_heredocs(t_heredocs **self, char *key, int len_key, t_bool minus)
{
	*self = ft_memalloc(sizeof(t_heredocs));
	(*self)->key = ft_strdup(key);
	(*self)->quoted = quoted_gold_key(key);
	(*self)->len_key = len_key;
	(*self)->minus = minus;
	(*self)->closed = false;
	init_tagstokens(&(*self)->tagstokens, NULL, NULL);
	(*self)->in_cmdsubst = false;
}

void	check_stack(t_heredocs *self, char *tag)
{
	char		*last_stack;
	char		*tmp_tag;

	last_stack = vindex_pylst(self->stack, -1);
	if (ft_strequ(tag, last_stack))
	{
		pop_pylst(&self->stack, -1);
		if (len_pylst(self->stack) == 0)
			self->in_cmdsubst = false;
	}
	else if (ft_strequ(tag, "QUOTE") && !ft_strequ(last_stack, "DQUOTES"))
		push_pylst(&self->stack, tag, 0, _ptr);
	else if (ft_strequ(tag, "DQUOTES") && !ft_strequ(last_stack, "QUOTE"))
		push_pylst(&self->stack, tag, 0, _ptr);
	else if (search_value(g_grammar->opening_tags, tag) && \
			!ft_strequ(last_stack, "QUOTE"))
	{
		if (ft_strequ(last_stack, "DQUOTES") && \
				(tmp_tag = search_value(g_grammar->dquotes_opening_tags, tag)))
			push_pylst(&self->stack, tmp_tag, 0, _ptr);
		else
		{
			tmp_tag = search_value(g_grammar->opening_tags, tag);
			push_pylst(&self->stack, tmp_tag, 0, _ptr);
		}
	}
}

void	add_tags_tokens(t_heredocs *self, char *tag, char *token)
{
	char	*tmp_tag;

	if (self->quoted)
		tag = "STMT";
	else if (!self->in_cmdsubst)
	{
		if ((tmp_tag = search_value(g_grammar->dquotes_opening_tags, tag)))
		{
			self->in_cmdsubst = true;
			push_pylst(&self->stack, tmp_tag, 0, _ptr);
		}
		else
			tag = in(tag, "VAR", "STMT", "SPACES", "NEW_LINE", NULL) ?\
				  tag : "STMT";
	}
	else
		check_stack(self, tag);
	append_tagstokens(tag, token);
}

void	striplines(t_heredocs *self)
{
	size_t		index;
	t_bool	new_line;
	char	*tag;
	char	*token;

	index = 0;
	new_line = true;
	while (index < self->tagstokens->length)
	{
		token = vindex_pylst(self->tagstokens->tokens, index);
		tag = vindex_pylst(self->tagstokens->tags, index);
		if (ft_strequ(tag, "NEW_LINE"))
			new_line = true;
		else if (ft_strequ(tag, "SPACES") && new_line)
		{
			//replace_first_tab seem to not exist.
			//Check allocation, set _ptr by default.
			//update_pylst(self->tagstokens->tokens, index, \
			//		replace_first_tab(token), 0, _ptr);
		}
		else
			new_line = false;
		index++;
	}
}

void	close_heredoc(t_heredocs *self)
{
	//self->tagstokens = copytt(self, 0, -self->len_key);//Seem to not exist
	self->tagstokens->not_heredocs = false;
	if (self->minus)
		striplines(self);
	check_syntax_tagstokens(self->tagstokens); //Check if check_stack in python is check_syntax_tagstokens
	self->closed = true;
}

static char	*quick_join(char *s1, char *s2, t_bool free_s1, t_bool free_s2)
{
	return (ft_fstrjoin(&s1, &s2, free_s1, free_s2));
}

char	*str_heredocs(t_heredocs *self)
{
	char	*str;
	char	*bool_str;

	str = quick_join("\nHEREDOC", self->key, false, false);
	str = quick_join(str, " | closed: ", true, false);
	bool_str = self->closed ? "True" : "False";
	str = quick_join(str, bool_str, true, false);
	str = quick_join(str, " | Minus: ", true, false);
	bool_str = self->minus ? "True" : "False";
	str = quick_join(str, bool_str, true, false);
	str = quick_join(str, "\n", true, false);
	str = quick_join(str, "DOC:\n", true, false);
	str = quick_join(str, str_tagstokens(self->tagstokens), true, true);
	return (str);
}
