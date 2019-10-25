/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   is_newline_ttm.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: epoggio <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/03 22:27:14 by epoggio      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/03 22:32:22 by epoggio     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ttm.h"

static t_heredocs	*get_heredoc(t_pylst *list_param, char **gold_key)
{
	t_heredocs	*heredoc;
	char		*tmp;

	tmp = (char *)vindex_pylst(list_param, 0);
	init_heredocs(&heredoc,
					tmp,
					*((int *)vindex_pylst(list_param, 1)),
					*((int *)vindex_pylst(list_param, 2)));
	modify_gold_key(tmp);
	*gold_key = tmp;
	return (heredoc);
}

static	t_bool		full_heredoc(t_tags_tokens_monitor *self,
							t_heredocs *heredoc, char *gold_key, t_bool minus)
{
	char	*key;
	t_bool	not_end;

	key = ft_strnew(0);
	not_end = next_ttm(self, true);
	while (not_end)
	{
		if (ft_strequ(key, gold_key))
		{
			close_heredocs(heredoc);
			break ;
		}
		add_tags_tokens_heredocs(heredoc, self->tag, self->token);
		key = get_key(key, self->tag, self->token, minus);
		if (ft_strequ(self->tag, "NEW_LINE"))
		{
			ft_strdel(&key);
			key = ft_strnew(0);
		}
		not_end = next_ttm(self, true);
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

void				is_newline_ttm(t_tags_tokens_monitor *self)
{
	t_pylst		*list_param;
	char		*gold_key;
	t_heredocs	*heredoc;
	t_bool		not_end;
	t_bool		minus;

	list_param = NULL;
	not_end = true;
	minus = false;
	gold_key = NULL;
	while (self->heredocs_keys &&
			(list_param = pop_pylst(&self->heredocs_keys, 0)) && not_end)
	{
		minus = *((int *)vindex_pylst(list_param, 2));
		heredoc = get_heredoc(list_param, &gold_key);
		push_pylst(&g_heredocs, heredoc, 0, _heredocs);
		not_end = full_heredoc(self, heredoc, gold_key, minus);
		free_pylst(&list_param, 42);
	}
	reset_ttm(self);
}
