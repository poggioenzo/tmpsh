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

#ifndef STANDARD_MOVE_H
# define STANDARD_MOVE_H

# include "tmpsh.h"

void		move_left(t_line *shell_repr, t_cursor *cursor);
void		move_right(t_line *shell_repr, t_cursor *cursor);
void		move_down(t_line *shell_repr, t_cursor *cursor);
void		move_up(t_line *shell_repr, t_cursor *cursor);

#endif
