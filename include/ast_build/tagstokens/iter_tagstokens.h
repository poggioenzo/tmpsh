/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   iter_tagstokens.h                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: epoggio <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/16 12:46:40 by epoggio      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/16 12:47:11 by epoggio     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef ITER_TAGSTOKENS_H
# define ITER_TAGSTOKENS_H

t_bool	iter_tagstokens(t_tagstokens *self, char *token, char *tag);
void	break_tagstokens(t_tagstokens *self);

#endif
