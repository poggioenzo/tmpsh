/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   in_command_sh_ttm.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: epoggio <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/03 22:15:56 by epoggio      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/03 22:16:35 by epoggio     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ttm.h"

static int		search_end(char *tag)
{
	if (in_grammar(tag, "ABS_TERMINATOR"))
		return (1);
	if (in_grammar(tag, "REDIRECTION"))
		return (1);
	return (in(tag, "END_BRACE", "END_BRACKET", NULL));
}

/*
** in_command_sh_ttm:
**
** description:
** If the command it's at the beginning check validity for CURSH or SUBSH.
** Else it's replace COMMAND_SH grand child symbol by STMT.
**
** parameter:
** - (t_tags_tokens_monitor*) self : actual tagstokensmonitor.
*/

void			in_command_sh_ttm(t_tags_tokens_monitor *self)
{
	int		end;
	int		ret;

	if (self->begin_cmd)
	{
		in_sub_process_ttm(self);
		ret = next_ttm(self, false);
		if (ft_strequ(self->tag, "SPACES"))
			ret = next_ttm(self, false);
		end = search_end(self->tag);
		if (ret && !end)
		{
			self->tt->valid = false;
			self->tt->token_error = self->token;
		}
		else if (ret && end)
			reset_ttm(self);
	}
	else
	{
		end = skip_openning_tagstokens(self->tt, self->i, NULL) - 1;
		update_pylst(self->tt->tags, self->i, "STMT", 0, _ptr);
		if (end < (int)self->tt->length)
			update_pylst(self->tt->tags, end, "STMT", 0, _ptr);
	}
}
