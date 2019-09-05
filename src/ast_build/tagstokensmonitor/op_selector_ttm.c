/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   op_selector_ttm.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: epoggio <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/03 22:33:52 by epoggio      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/04 19:18:26 by epoggio     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ttm.h"

static	t_bool	assignation_braceparam(t_tags_tokens_monitor *self)
{
	return (ft_strequ(self->tag, "BRACEPARAM")
			|| in_grammar(self->tag, "ASSIGNATION_SYMBOL"));
}

static	void	is_assignation(t_tags_tokens_monitor *self)
{
	if (self->i != 0 && !ft_strequ(vindex_pylst(
					self->tt->tags, self->i - 1), "STMT"))
	{
		update_pylst(self->tt->tags, self->i, "STMT", 0, _ptr);
		self->begin_cmd = false;
	}
}

static	void	braceparam_or_assignation(t_tags_tokens_monitor *self)
{
	if (ft_strequ(self->tag, "BRACEPARAM"))
		is_braceparam_ttm(self);
	else
		is_assignation(self);
}

/*
** op_selector_ttm:
**
** description:
** Dispatcher in function of the operator tag or the STMT tag.
**
** parameter:
** - (t_tags_tokens_monitor*) self : actual tagstokensmonitor.
*/

void			op_selector_ttm(t_tags_tokens_monitor *self)
{
	if (self->tt->valid)
	{
		if (ft_strequ(self->tag, "STMT"))
			self->begin_cmd = check_aliases_ttm(self);
		else if (assignation_braceparam(self))
			braceparam_or_assignation(self);
		else if (ft_strequ(self->tag, "DQUOTES"))
			is_dquotes_ttm(self);
		else if (ft_strequ(self->tag, "QUOTE"))
			is_quote_ttm(self);
		else if (ft_strequ(self->tag, "NEW_LINE"))
			is_newline_ttm(self);
		else if (in_grammar(self->tag, "ABS_TERMINATOR"))
			is_abs_terminator_ttm(self);
		else if (in(self->tag, "CURSH", "SUBSH", NULL))
			in_command_sh_ttm(self);
		else if (search_value(g_grammar->opening_tags, self->tag))
			in_sub_process_ttm(self);
		else if (in(self->tag, "HEREDOC", "HEREDOCMINUS", NULL))
			is_heredocs_ttm(self);
		else if (in_grammar(self->tag, "REDIRECTION"))
			in_redirection_ttm(self);
		else if (ft_strequ(self->tag, vindex_pylst(self->opened, -1)))
			pop_pylst(&self->opened, -1);
	}
}
