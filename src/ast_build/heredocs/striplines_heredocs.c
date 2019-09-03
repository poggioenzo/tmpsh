/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   striplines_heredocs.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: epoggio <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/03 22:08:54 by epoggio      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/03 22:09:59 by epoggio     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heredocs.h"

/*
** striplines_heredocs:
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

static char		*replace_first_tab(char *tok)
{
	char	*str;

	str = ft_strdup(tok + ft_strcspn(tok, "\t"));
	return (str);
}

void			striplines_heredocs(t_heredocs *self)
{
	size_t	index;
	t_bool	new_line;
	char	*tag;
	char	*token;

	index = 0;
	new_line = true;
	while (index < self->tagstokens->length)
	{
		token = vindex_pylst(self->tagstokens->tokens, index);
		tag = vindex_pylst(self->tagstokens->tags, index);
		if (ft_strequ(tag, "NEW_LINE"))
			new_line = true;
		else if (ft_strequ(tag, "SPACES") && new_line)
		{
			token = replace_first_tab(token);
			update_pylst(self->tagstokens->tokens, index, \
					(token),
					ft_strlen(token) + 1 * sizeof(char), _chare);
		}
		else
			new_line = false;
		index++;
	}
}
