/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   init_heredocs.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: epoggio <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/03 22:06:08 by epoggio      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/28 09:52:33 by epoggio     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heredocs.h"

/*
** init_heredocs:
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

void	init_heredocs(t_heredocs **self, char *key, int len_key, t_bool quoted)
{
	*self = ft_memalloc(sizeof(t_heredocs));
	(*self)->key = key;
	(*self)->len_key = len_key;
	(*self)->quoted = quoted;
	if ((*self)->quoted)
	{
		(*self)->len_key++;
		(*self)->quoted = !dquoted_gold_key(key);
	}
	(*self)->closed = false;
	(*self)->in_cmdsubst = false;
	init_tagstokens(&(*self)->tagstokens, NULL, NULL);
	(*self)->tagstokens->not_heredocs = false;
}
