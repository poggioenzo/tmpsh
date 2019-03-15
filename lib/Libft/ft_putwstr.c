/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_putwstr.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: simrossi <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/27 16:13:52 by simrossi     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/02 13:30:04 by simrossi    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_putwstr(wchar_t *str, int fd)
{
	size_t printed;

	printed = 0;
	while (*str)
		printed += ft_putwchar(*str++, fd);
	return (printed);
}
