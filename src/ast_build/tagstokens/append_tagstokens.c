/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   append_tagstokens.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: epoggio <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/17 21:12:19 by epoggio      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/17 21:15:53 by epoggio     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "tagstokens.h"

static	void	append_tag(t_pylst **tag_stack, char *tag)
{
	push_pylst(tag_stack, tag, 0, _ptr);
}

/*
** stack_append_tagstokens:
**
** Params:
** @self: actual tagstokens.
** @tag: string of the tag to append.
**
** Append tag to pylst self->stack.
*/

void			stack_append_tagstokens(t_tagstokens *self, char *tag)
{
	append_tag(&self->stack, tag);
}

/*
** append_tag_tagstokens:
**
** Params:
** @self: actual tagstokens.
** @tag: string of the tag to append.
**
** Append tag to pylst self->tags.
*/

void			append_tag_tagstokens(t_tagstokens *self, char *tag)
{
	append_tag(&self->tags, tag);
}

/*
** append_token_tagstokens:
**
** Params:
** @self: actual tagstokens.
** @token: string of the token to append.
**
** Append token to pylst self->tokens.
*/

void			append_token_tagstokens(t_tagstokens *self, char *token)
{
	push_pylst(&(self->tokens), token, (ft_strlen(token) + 1) *\
			sizeof(char), _chare);
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

void			append_tagstokens(t_tagstokens *self, char *token, char *tag)
{
	append_tag_tagstokens(self, tag);
	append_token_tagstokens(self, token);
	self->length++;
}
