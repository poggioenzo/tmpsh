/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_itoa.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: simrossi <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/13 10:29:14 by simrossi     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/14 09:59:45 by simrossi    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char			*ft_itoa(int nbr)
{
	int		len;
	char	*str;
	int		negativ;

	len = ft_nbrlen(nbr);
	negativ = nbr < 0;
	if (!(str = (char *)MALLOC(sizeof(char) * (len + 1))))
		return (NULL);
	str[len] = '\0';
	while (len)
	{
		str[len - 1] = ft_abs(nbr % 10) + '0';
		nbr /= 10;
		len--;
	}
	if (negativ)
		str[0] = '-';
	return (str);
}

char			*ft_utoa(unsigned int nbr)
{
	char	*return_str;
	int		len;

	len = ft_unbrlen(nbr);
	if (!(return_str = (char *)MALLOC(sizeof(char) * (len + 1))))
		return (NULL);
	return_str[len--] = '\0';
	while (len >= 0)
	{
		return_str[len--] = nbr % 10 + '0';
		nbr /= 10;
	}
	return (return_str);
}
