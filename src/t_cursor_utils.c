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

#include "t_cursor_utils.h"
#include "libft.h"
#include "t_caps_utils.h"

void	alloc_cursor(t_cursor **cursor)
{
	*cursor = (t_cursor *)ft_memalloc(sizeof(t_cursor));
	(*cursor)->row = 0;
	(*cursor)->column = 0;
}

int		dealloc_cursor(t_cursor **cursor, int status)
{
	FREE(*cursor);
	*cursor = NULL;
	return (status);
}

void	show_cursor(char letter)
{
	ft_printf("%s%c%s", g_caps->video, letter, g_caps->reset_video);
}
