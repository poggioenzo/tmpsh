/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   string_displayers.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: simrossi <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/27 15:22:44 by simrossi     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/14 09:05:37 by simrossi    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "printf.h"

/*
** Functions to use our chained list of t_fcts to display the right
** desired type. Format the string with differents utils function.
*/

/*
** display_ascii:
**
** Display standard string of char * returned by a t_fcts->string_maker
** function.
** Format the field of the string, depending if it's manpiulating a number
** converted to a string or simple string.
*/

int		display_ascii(va_list args, t_prt_opt *option, t_fcts *prt_manager, \
		int fd)
{
	int		octets;
	char	*format_str;

	octets = 0;
	while (!ft_strequ(option->full_specifier, prt_manager->key))
		prt_manager = prt_manager->next;
	if (!(format_str = prt_manager->string_maker(args, option, &octets)))
		return (-1);
	if (option->category == 1 && !set_nbfield(option, &format_str, &octets))
		return (-1);
	if (option->category == 2 && !set_strfield(option, &format_str, &octets))
		return (-1);
	if (option->specifier == 'c')
		ft_putchar_fd(*format_str, fd);
	else
		ft_putstr_fd(format_str, fd);
	ft_strdel(&format_str);
	return (octets);
}

/*
** display_unicode:
**
** Display a wchar_t * string. Adjust field and write it.
*/

int		display_unicode(va_list args, t_prt_opt *option, t_wfcts *prt_manager, \
		int fd)
{
	int		octets;
	wchar_t	*format_str;

	octets = 0;
	while (!ft_strequ(option->full_specifier, prt_manager->key))
		prt_manager = prt_manager->next;
	if (!(format_str = prt_manager->string_maker(args, option, &octets)))
		return (-1);
	if (!set_unicode_field(option, &format_str, &octets))
		return (-1);
	ft_putwstr(format_str, fd);
	FREE(format_str);
	return (octets);
}
