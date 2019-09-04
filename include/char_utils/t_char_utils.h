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

#ifndef T_CHAR_UTILS_H
# define T_CHAR_UTILS_H

# include "tmpsh.h"

int			extend_char(t_char *old_chars, t_char *char_to_add);
void		update_position(t_char *char_lst);
int			char_lst_len(t_char *char_lst);
int			char_lock_len(t_char *char_lst);
void		increment_char_end(t_char *char_lst);
#endif
