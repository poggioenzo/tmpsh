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

#ifndef HISTORY_MANAGER_UTILS_H
# define HISTORY_MANAGER_UTILS_H

# include "tmpsh.h"

void	select_current_history(char *key, t_hist **history, int is_repetition);
void	clean_lastest_history(int is_repetition, t_line *shell_repr, \
		t_cursor *cursor, t_hist *curr_history);

#endif
