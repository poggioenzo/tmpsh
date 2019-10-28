/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   str_command_tagstokens.c                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: epoggio <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/27 20:25:09 by epoggio      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/27 20:25:55 by epoggio     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "tagstokens.h"

char	*str_command_tagstokens(t_tagstokens *self)
{
	char	*tok;
	char	*tag;
	char	*str;
	char	*local;

	str = ft_strnew(0);
	while (iter_tagstokens(self, &tok, &tag))
	{
		local = " ";
		if (ft_strequ("SPACES", tag))
			str = ft_fstrjoin(&str, &local, TRUE, FALSE);
		else if (ft_strequ("SUBAST", tag))
		{
			local = YELLOW"subast"WHITE;
			str = ft_fstrjoin(&str, &local, TRUE, FALSE);
		}
		else
			str = ft_fstrjoin(&str, &tok, TRUE, FALSE);
	}
	return (str);
}
