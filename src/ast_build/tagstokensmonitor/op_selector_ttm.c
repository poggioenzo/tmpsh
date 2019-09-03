/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   op_selector_ttm.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: epoggio <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/03 22:33:52 by epoggio      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/03 22:34:11 by epoggio     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ttm.h"

/*
** op_selector_ttm:
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

void	op_selector_ttm(t_tags_tokens_monitor *self)
{
	if (self->tt->valid)
	{
		if (ft_strequ(self->tag, "STMT"))
			self->begin_cmd = check_aliases_ttm(self);
		else if (ft_strequ(self->tag, "BRACEPARAM"))
			is_braceparam_ttm(self);
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
