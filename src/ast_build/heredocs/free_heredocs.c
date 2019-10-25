/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   free_heredocs.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: epoggio <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/03 22:05:43 by epoggio      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/03 22:05:46 by epoggio     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heredocs.h"

/*
** free_heredocs:
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

int			free_heredocs(t_heredocs **self, int status)
{
	ft_strdel(&(*self)->key);
	free_tagstokens(&(*self)->tagstokens, status);
	ft_memdel((void **)self);
	return (status);
}

void	free_heredocs_type(void *heredoc)
{
	free_heredocs((t_heredocs **)heredoc, 42);
}
