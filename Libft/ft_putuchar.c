/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_putuchar.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: simrossi <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/27 16:13:24 by simrossi     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/02 13:31:54 by simrossi    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int		ft_putuchar(unsigned char c)
{
	wchar_t print_value;

	print_value = c;
	return (ft_putwchar(print_value, 1));
}
