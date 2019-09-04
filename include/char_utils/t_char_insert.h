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

#ifndef T_CHAR_INSERT_H
# define T_CHAR_INSERT_H

# include "tmpsh.h"
# include "cursor_dependent_selection.h"

void		insert_string(t_char **char_lst, char *string, int lock);
void		insert_char(t_char **char_lst, char letter, int lock);
void		cursor_insert(t_line *shell_repr, char letter, t_cursor *cursor);
#endif
