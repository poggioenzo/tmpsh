#include "ttm.h"


/*
** in_command_sh_ttm:
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

static int		search_end(char *tag)
{
	if (in_grammar(tag, "ABS_TERMINATOR"))
		return (1);
	if (in_grammar(tag, "REDIRECTION"))
		return (1);
	return (in(tag, "END_BRACE", "END_BRACKET", NULL));
}

void	in_command_sh_ttm(t_tags_tokens_monitor *self)
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
			reset_ttm(self); // SHould be an other function name
	}
	else
	{
		end = skip_openning_tagstokens(self->tt, self->i, NULL) - 1;
		update_pylst(self->tt->tags, self->i, "STMT", 0, _ptr);
		if (end < (int)self->tt->length)
			update_pylst(self->tt->tags, end, "STMT", 0, _ptr);
	}
}
