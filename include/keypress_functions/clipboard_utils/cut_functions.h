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

#ifndef CUT_FUNCTIONS_H
# define CUT_FUNCTIONS_H

# include "tmpsh.h"

void		line_cut(t_line	*shell_repr, t_cursor *cursor);
void		cut_next_word(t_line *shell_repr, t_cursor *cursor);
void		cut_prev_word(t_line *shell_repr, t_cursor *cursor);
void		paste_clipboard(t_line *shell_repr, t_cursor *cursor);

#endif
