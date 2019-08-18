/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tagstokens.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: epoggio <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/16 16:50:43 by epoggio      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/17 21:19:40 by epoggio     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "tagstokens.h"

/*
** init_tagstokens:
**
** Params:
** @self: adress of a t_tagstokens pointer.
** @tokens: pylst of token or NULL.
** @tags: pylst of tag or NULL.
**
** Create and initialize a tagstokens.
**
** Attributs:
** @tokens: pylst of token.
** @tags: pylst of tag.
** @stack: pylst of tag left after check_syntax_tagstokens.
** @token_error: string of the token error.
** @valid: True if tagstokens syntax is valid else False.
** @incomplete: False if tagstokens syntax is complete else True.
** @length: int that represent length of the tokens.
** @iter: int to iterate through the tagstokens.
*/

void	init_tagstokens(t_tagstokens **self, t_pylst *tokens, t_pylst *tags)
{
	*self = (t_tagstokens*)ft_memalloc(sizeof(t_tagstokens));
	(*self)->tokens = tokens;
	(*self)->tags = tags;
	(*self)->stack = NULL;
	(*self)->token_error = NULL;
	(*self)->valid = TRUE;
	(*self)->incomplete = FALSE;
	(*self)->length = 0;
	(*self)->iter = -1;
	update_length_tagstokens(*self);
}

/*
** input_init_tagstokens:
**
** Params:
** @self: adress of a t_tagstokens pointer.
** @input: raw input command to tokenize and tag.
**
** Create a tagstokens. Set the tokenise input as tokens and get
** get tags form it. If input is NULL or full of spaces then self is NULL.
*/

void	input_init_tagstokens(t_tagstokens **self, char *input)
{
	*self = NULL;
	if (!(input) || ft_strspn(input, g_grammar->spaces) == ft_strlen(input))
		return ;
	init_tagstokens(self, NULL, NULL);
	tokenize(input, &((*self)->tokens));
	update_length_tagstokens(*self);
	get_tag_tagstokens(*self);
	check_syntax_tagstokens(*self);
}
