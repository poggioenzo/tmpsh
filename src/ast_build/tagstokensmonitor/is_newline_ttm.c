/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   is_newline_ttm.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: epoggio <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/03 22:27:14 by epoggio      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/28 10:00:39 by epoggio     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ttm.h"

static t_bool		remove_next_ttm(t_tags_tokens_monitor *self)
{
	int		prev;
	t_bool	ret;

	prev = self->i;
	ret = next_ttm(self);
	if (ret)
		delitems_tagstokens(self->tt, prev, prev + 1, 42);
	self->i = prev;
	return (ret);
}

static	t_bool		full_heredoc(t_tags_tokens_monitor *self,
							t_heredocs *heredoc, char *gold_key)
{
	char	*key;
	t_bool	not_end;

	key = ft_strnew(0);
	not_end = next_ttm(self);
	while (not_end || ft_strequ(key, gold_key))
	{
		if (ft_strequ(key, gold_key) && ft_strequ(self->tag, "NEW_LINE"))
		{
			close_heredocs(heredoc);
			break ;
		}
		add_tags_tokens_heredocs(heredoc, self->tag, self->token);
		key = get_key(key, self->tag, self->token, false);
		if (ft_strequ(self->tag, "NEW_LINE"))
		{
			ft_strdel(&key);
			key = ft_strnew(0);
		}
		not_end = remove_next_ttm(self);
	}
	return (ft_strdel_out(&key, not_end));
}

/*
** is_newline_ttm:
**
** description:
** After newline create all presente heredoc and insert then in g_heredocs.
**
** parameter:
** - (t_tags_tokens_monitor*) self : actual tagstokensmonitor.
*/

void				is_newline_ttm(t_tags_tokens_monitor *self, t_bool reset)
{
	static int			index = 0;
	char				*gold_key;
	t_heredocs			*heredoc;
	t_bool				not_end;

	not_end = true;
	gold_key = NULL;
	heredoc = NULL;
	if (reset)
	{
		index = 0;
		return ;
	}
	while (self->tt->not_heredocs && index < len_pylst(g_heredocs)
			&& (heredoc = vindex_pylst(g_heredocs, index++)) && not_end)
	{
		gold_key = ft_strdup(heredoc->key);
		not_end = full_heredoc(self, heredoc, gold_key);
		ft_strdel(&gold_key);
	}
	reset_ttm(self);
}
