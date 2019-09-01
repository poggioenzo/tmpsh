#include "ttm.h"


/*
** check_alias_ttm:
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

t_bool		check_aliases_ttm(t_tags_tokens_monitor *self)
{
	char	*result_alias;
	t_bool	assignation;

	result_alias = "";
	assignation = self->i + 1 < (int)self->tt->length && \
				  in(find_next_token(self->tt, self->i + 1, false), \
						  "ASSIGNATION_EQUAL", "CONCATENATION", NULL);
	if (!assignation && self->begin_cmd && self->token\
			&& (search_value(g_alias, self->token) && \
			 !in_pylst_chare(self->token, g_passed_alias)))
	{
		result_alias = search_value(g_alias, self->token);
		self->begin_cmd = ft_isspace(result_alias[ft_strlen(result_alias) - 1]);
		push_pylst(&g_passed_alias, self->token, 0, _ptr); // Check memory.
		replace_alias_tagstokens(self->tt, result_alias, self->i);
		if (self->begin_cmd)
		{
			reset_ttm(self);
			return (true);
		}
	}
	else if (assignation)
	{
		if (!self->begin_cmd)
			update_pylst(self->tt->tags, self->i + 1, "STMT", 0, _ptr);
		else
			return (true);
	}
	return (self->i - 1 > 0 &&
			in(find_prev_token(self->tt, self->i - 1, false), \
				"ASSIGNATION_EQUAL", "CONCATENATION", NULL));
}
