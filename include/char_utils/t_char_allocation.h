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

#ifndef T_CHAR_ALLOCATION_H
# define T_CHAR_ALLOCATION_H

# include "tmpsh.h"

void	push_end_char(t_char **char_node, char letter, int lock);
void	free_t_char(t_char **char_node);
int		free_t_char_lst(t_char **char_lst, int status);
void	create_char(t_char	**char_node, char letter, int position, int lock);

#endif
