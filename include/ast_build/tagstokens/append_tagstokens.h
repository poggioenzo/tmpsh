/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   append_tagstokens.h                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: epoggio <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/17 21:07:11 by epoggio      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/17 21:07:15 by epoggio     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef APPEND_TAGSTOKENS_H
# define APPEND_TAGSTOKENS_H

void append_tagstokens(t_tagstokens *self, char *token, char *tag);
void append_token_tagstokens(t_tagstokens *self, char *token);
void append_tag_tagstokens(t_tagstokens *self, char *tag);
void stack_append_tagstokens(t_tagstokens *self, char *tag);

#endif
