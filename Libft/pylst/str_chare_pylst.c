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

#include "libft.h"

/*
** str_chare_pylst:
**
** Arguments, in order :
** @pylst: choosen list.
**
** Return a string of python'style list of pylst.
** ! Work only if pylst values are char * !
*/

char	*str_chare_pylst(t_pylst *pylst)
{
	char *str;
	char *cara;

	if (!pylst)
		return (ft_strdup("[]\n"));
	cara = "['";
	str = join_pylst(pylst, "', '");
	str = ft_fstrjoin(&cara, &str, FALSE, TRUE);
	cara = "']\n";
	str = ft_fstrjoin(&str, &cara, TRUE, FALSE);
	return (str);
}
