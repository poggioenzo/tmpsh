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

#include "tmpsh.h"
#include "libft.h"

/*
** convert_char:
**
** Return the ascii value corresponding to given escaped char.
*/

char	convert_char(char c)
{
	if (c == 'n')
		return ('\n');
	else if (c == 't')
		return ('\t');
	else if (c == 'r')
		return ('\r');
	else if (c == 'v')
		return ('\v');
	else if (c == 'a')
		return ('\a');
	else if (c == 'b')
		return ('\b');
	else if (c == 'f')
		return ('\f');
	else if (c == '\\')
		return ('\\');
	return (0);
}

/*
** replace_escape:
**
** Parse an entire string and replace escaped char
** by their representation.
*/

void	replace_escape(char *str)
{
	char	new_char;

	while (*str)
	{
		if (*str == '\\')
		{
			new_char = convert_char(*(str + 1));
			if (new_char)
			{
				*str = new_char;
				ft_strcpy(str + 1, str + 2);
			}
		}
		str++;
	}
}

/*
** built_echo:
**
** echo - Write argument to standard output.
**
** Synopsis : echo [string ...]
**
** Options :
** -n : avoid printing a newline.
*/

int		built_echo(char **args, NOT_USE(char **environ))
{
	int		newline;
	int		error;

	newline = true;
	error = false;
	if (ft_strequ(*args, "-n"))
	{
		args++;
		newline = false;
	}
	while (*args)
	{
		replace_escape(*args);
		error = ft_printf(*args) == -1 ? true : false;
		if (error == false && *(args + 1))
			error = ft_printf(" ") == -1 ? true : false;
		args++;
	}
	if (error == false && newline)
		error = ft_printf("\n") == -1 ? true : false;
	return (error == true ? -1 : 0);
}
