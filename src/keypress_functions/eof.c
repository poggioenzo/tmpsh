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

#include "char_utils.h"
#include "shell_setup.h"

/*
** check_eof:
**
** Whenever CTRL-D is pressed, check if the string if the prompt is empty,
** leave the program if it the case.
*/

void		check_eof(t_line *shell_repr)
{
	t_char	*first_unlock;

	first_unlock = get_unlocked_char(shell_repr->chars);
	if (!first_unlock && !shell_repr->next)
		shell_exit(0);
}
