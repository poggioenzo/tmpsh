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

#ifndef T_LINE_ALLOCATION_H
# define T_LINE_ALLOCATION_H

# include "tmpsh.h"

int			free_t_line(t_line **line_lst, int status);
int			free_t_line_lst(t_line **line_lst, int status);
void		create_t_line(t_line **new_line, int position);
void		push_end_line(t_line **line_lst);

#endif
