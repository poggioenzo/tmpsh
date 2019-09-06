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

#include <ncurses.h>
#include <term.h>
#include "t_caps_utils.h"
#include "libft.h"
#include "environ_utils.h"

/*
** alloc_capabilities_struct:
**
** Allocate a t_caps * element, prepare all termcaps strings in different
** attribute of our structure.
*/

t_caps	*g_caps;

void		alloc_capabilities_struct(void)
{
	if (!ft_getenv("TERM"))
		ft_setenv("TERM", "screen");
	if (tgetent(NULL, ft_getenv("TERM")) == -1)
		exit(-1);
	g_caps = (t_caps *)ft_memalloc(sizeof(t_caps));
	g_caps->clear = tgetstr("cl", NULL);
	g_caps->video = tgetstr("mr", NULL);
	g_caps->reset_video = tgetstr("me", NULL);
	g_caps->hide_cursor = tgetstr("vi", NULL);
	g_caps->reset_cursor = tgetstr("ve", NULL);
	g_caps->save_pos = tgetstr("sc", NULL);
	g_caps->reset_pos = tgetstr("rc", NULL);
	g_caps->del_line = tgetstr("dl", NULL);
	g_caps->start_line = tgetstr("cr", NULL);
	g_caps->move_up = tgetstr("up", NULL);
	g_caps->move_down = tgetstr("do", NULL);
}
