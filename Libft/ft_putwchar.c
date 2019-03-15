/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_putwchar.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: simrossi <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/27 16:11:02 by simrossi     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/02 13:29:41 by simrossi    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static unsigned char	first_byte(wchar_t *c, size_t bytes)
{
	unsigned char c_byte;

	c_byte = 0b1111 % ft_pow(2, bytes);
	c_byte <<= 8 - bytes;
	c_byte |= *c >> 6 * (bytes - 1);
	*c %= ft_pow(2, (bytes - 1) * 6);
	return (c_byte);
}

size_t					ft_putwchar(wchar_t c, int fd)
{
	int bytes;
	int index;
	int print_index;
	int wchar_lst[4];

	index = 0;
	if (ft_isascii(c))
		return (write(fd, &c, 1));
	bytes = determine_bytes(c);
	wchar_lst[index++] = first_byte(&c, bytes--);
	while (bytes)
	{
		bytes--;
		wchar_lst[index++] = 0b10000000 | (c >> (bytes * 6));
		c %= ft_pow(2, bytes * 6);
	}
	print_index = 0;
	while (print_index < index)
		write(fd, wchar_lst + print_index++, 1);
	return (index);
}
