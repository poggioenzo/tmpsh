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

#ifndef CURSOR_DEPENDENT_SELECTION_UTILS_H
# define CURSOR_DEPENDENT_SELECTION_UTILS_H

void			research_prev_info(t_line *shell_repr, t_cursor *cursor, \
		t_cursor *word_cursor, t_char **search_char);
void			set_last_pos(t_line *shell_repr, t_cursor *cursor);
void			skip_empty_char(t_line **cursor_line, t_char **search_char);

#endif
