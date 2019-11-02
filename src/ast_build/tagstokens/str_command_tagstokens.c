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

char *str_replace(char **str, char this, char by)
{
	int i;

	i = 0;
	while (*str[i])
	{
		if (*str[i] == this)
			*str[i] = by;
		i++;
	}
	return (*str);
}

char	*str_command_tagstokens(t_tagstokens *self)
{
	char	*tok;
	char	*tag;
	char	*str;
	char	*local;


	str = ft_strnew(0);
	while (iter_tagstokens(self, &tok, &tag))
	{
		ft_printf(PURPLE"%d\n"WHITE, ft_strequ("NEW_LINE", tag));
		local = " ";
		if (ft_strequ("SPACES", tag))
			str = ft_fstrjoin(&str, &local, TRUE, FALSE);
		else if (ft_strequ("NEW_LINE", tag))
		{
			local = ";";

			str = ft_fstrjoin(&str, &local, TRUE, FALSE);
		}
		else if (ft_strequ("SUBAST", tag))
		{
			local = YELLOW"subast"WHITE;
			str = ft_fstrjoin(&str, &local, TRUE, FALSE);
		}
		else
			str = ft_fstrjoin(&str, &tok, TRUE, FALSE);
	}
	str = str_replace(&str, '\n', ' ');
	ft_printf(PURPLE"%s\n"WHITE, str);
	return (str);
}
