/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_printf.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: simrossi <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/27 16:18:59 by simrossi     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/02 13:38:24 by simrossi    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "printf.h"

/*
** find_delim_start:
**
** Find the first unescaped % symbol. Print caracters while
** moving on.
*/

int		find_delim_start(char **format, size_t *printed, int fd)
{
	while (**format && **format != '%')
	{
		*printed += write(fd, *format, 1);
		(*format)++;
	}
	if (**format == '%' && *(*format + 1) == '%')
	{
		*printed += write(fd, "%", 1);
		*format += 2;
		find_delim_start(format, printed, fd);
	}
	else if (**format == '%' && *(*format + 1) == '\0')
	{
		(*format)++;
		*printed = -1;
	}
	return (**format ? 1 : 0);
}

/*
** ft_parse_printf:
**
** Parsing the format string, and display each required format with
** differents utils.
** Loop to find a % symbol, parse the option the format, and display it
** if it's possible.
*/

int		ft_parse_printf(char *format, va_list args, t_fct_manager *manager, \
		int fd)
{
	size_t		printed;
	t_prt_opt	*curr_optn;
	int			opt_res;

	printed = 0;
	curr_optn = NULL;
	while (find_delim_start(&format, &printed, fd))
	{
		if (((opt_res = parse_option(&format, &curr_optn)) == -1))
			return (free_prt_opt(&curr_optn, -1));
		if (opt_res == 0)
		{
			write(fd, format++, 1);
		       	printed++;
			continue ;
		}
		if (curr_optn->category != 3)
			opt_res = display_ascii(args, curr_optn, manager->std_fcts, fd);
		else
			opt_res = display_unicode(args, curr_optn, manager->uni_fcts, fd);
		if (opt_res == -1)
			return (free_prt_opt(&curr_optn, -1));
		printed += opt_res;
		format++;
	}
	return (free_prt_opt(&curr_optn, printed));
}

/*
** ft_dprintf:
**
** Display a formated string according to given specifier and file descriptor.
*/

int		ft_dprintf(int fd, char *format, ...)
{
	va_list			args;
	t_fct_manager	*manager;
	int				printed;

	va_start(args, format);
	if (!(manager = setup_functions()))
		return (-1);
	printed = ft_parse_printf(format, args, manager, fd);
	free_manager(&manager);
	va_end(args);
	return (printed);
}

/*
** ft_printf:
**
** Display a formated string according to given specifier on stdin.
*/

int		ft_printf(char *format, ...)
{
	va_list			args;
	t_fct_manager	*manager;
	int				printed;

	va_start(args, format);
	if (!(manager = setup_functions()))
		return (-1);
	printed = ft_parse_printf(format, args, manager, 1);
	free_manager(&manager);
	va_end(args);
	return (printed);
}
