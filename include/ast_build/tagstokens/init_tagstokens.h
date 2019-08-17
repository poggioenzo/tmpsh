/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   init_tagstokens.h                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: epoggio <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/17 16:44:23 by epoggio      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/17 21:35:16 by epoggio     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef INIT_TAGSTOKENS_H
# define INIT_TAGSTOKENS_H

void	init_tagstokens(t_tagstokens **self, t_pylst *tokens, t_pylst *tags);
void	input_init_tagstokens(t_tagstokens **self, char *input);

#endif
