/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tagstokens.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: epoggio <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/16 16:50:43 by epoggio      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/16 16:53:01 by epoggio     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

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

void	update_length_tagstokens(t_tagstokens *self)
{
	self->length = len_pylst(self->tokens);
}

void	init_tagstokens(t_tagstokens **self, t_pylst *tokens, t_pylst *tags)
{
	*self = (t_tagstokens*)ft_memalloc(sizeof(t_tagstokens));
	(*self)->tokens = tokens;
	(*self)->tags = tags;
	(*self)->stack = NULL; // t_pylst *
	(*self)->token_error = NULL; // char *
	(*self)->valid = TRUE;
	(*self)->incomplete = FALSE;
	(*self)->length = 0;
	(*self)->iter = -1;
	// strip_tagstokens(self);
	update_length_tagstokens(*self);
}

void	get_tag_tagstokens(t_tagstokens *self)
{
	int		iter;
	int		len_tok;
	char	*tok;

	// char *tag;
	iter = 0;
	while (iter < self->length)
	{
		tok = (char *)get_value_pylst(self->tokens, iter);
		len_tok = ft_strlen(tok);
		if (in_pylst_chare(tok, g_grammar->leaf_op))
			push_pylst(&(self->tags), \
					search_value(g_grammar->reverse, tok), 0, _ptr);
		else if (ft_strspn(tok, g_grammar->spaces) == len_tok)
			push_pylst(&(self->tags), "SPACES", 0, _ptr);
		else if (len_tok > 1 && tok[0] == '$')
			push_pylst(&(self->tags), "VAR", 0, _ptr);
		else
			push_pylst(&(self->tags), "STMT", 0, _ptr);
		iter++;
	}
}
