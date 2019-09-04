/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   determine_bytes.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: simrossi <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/27 15:04:52 by simrossi     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/27 15:04:55 by simrossi    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FIND_TAGSTOKENS_H
# define FIND_TAGSTOKENS_H

int		find_prev_ind_token(t_tagstokens *self, int i);
int		find_next_ind_token(t_tagstokens *self, int i);
char	*find_prev_token(t_tagstokens *self, int i, t_bool get_token);
char	*find_next_token(t_tagstokens *self, int i, t_bool get_token);

#endif
