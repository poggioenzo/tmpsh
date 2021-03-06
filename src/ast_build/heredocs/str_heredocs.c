/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   str_heredocs.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: epoggio <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/03 22:06:38 by epoggio      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/28 09:53:07 by epoggio     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heredocs.h"

/*
** str_heredocs:
**
** description:
** describe what you function do.
**
** parameter:
** - (type) name : what is this param?
**
** return value:
** - (type) value : descibe output.
*/

static char	*quick_join(char *s1, char *s2, t_bool free_s1, t_bool free_s2)
{
	return (ft_fstrjoin(&s1, &s2, free_s1, free_s2));
}

char		*str_heredocs(t_heredocs *self)
{
	char	*str;
	char	*bool_str;

	str = quick_join("\nHEREDOC ", self->key, false, false);
	str = quick_join(str, " | closed: ", true, false);
	bool_str = self->closed ? GREEN"True"WHITE : RED"False"WHITE;
	str = quick_join(str, bool_str, true, false);
	str = quick_join(str, "\n", true, false);
	str = quick_join(str, "DOC:\n", true, false);
	str = quick_join(str, str_tagstokens(self->tagstokens), true, true);
	return (str);
}
