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

#include <stdarg.h>
#include "libft.h"

/*
** in:
**
** Check if the given string is contained in a serie
** of strings.
**
** return : - 1 if the string is inside.
**			- 0 if the string is unavailable.
**
** Exemple:
**
** in("test", "value1", "value2", "test", NULL); => return 1.
*/

int		in(char *value, ...)
{
	va_list		args;
	char		*next_str;
	int			contain;

	va_start(args, value);
	contain = 0;
	while ((next_str = va_arg(args, char *)) && !contain)
		contain = ft_strequ(value, next_str);
	va_end(args);
	return (contain);
}
