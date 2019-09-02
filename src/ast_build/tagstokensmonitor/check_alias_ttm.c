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

static t_bool get_assgt(t_tags_tokens_monitor *self, int up, int down, t_bool isdown)
{
	if (isdown)
	{
		return (up > down
				&& in(find_next_token(self->tt, down , false), \
				"ASSIGNATION_EQUAL", "CONCATENATION", NULL));
	}
	else
	{
		return (up > down
				&& in(find_prev_token(self->tt, up, false), \
				"ASSIGNATION_EQUAL", "CONCATENATION", NULL));
	}
	return (true);
}

t_bool		check_aliases_ttm(t_tags_tokens_monitor *self)
{
	char	*ret_alias;
	t_bool	assignation;

	ret_alias = "";
	assignation = get_assgt(self, (int)self->tt->length, self->i + 1, true);
	print_pylst_chare(g_passed_alias);
	if (!assignation && self->begin_cmd && self->token\
			&& (search_value(g_alias, self->token) && \
			 !in_pylst_chare(self->token, g_passed_alias)))
	{
		ret_alias = search_value(g_alias, self->token);
		self->begin_cmd = ft_isspace(ret_alias[ft_strlen(ret_alias) - 1]);
		// ft_printf(self->begin_cmd ? YELLOW"True\n"WHITE: PURPLE"False\n"WHITE);
		push_pylst(&g_passed_alias, self->token, 0, _ptr); // Check memory.
		replace_alias_tagstokens(self->tt, ret_alias, self->i);
		if (self->begin_cmd)
			return (reset_ttm_out(self, true));
	}
	else if (assignation)
	{
		if (!self->begin_cmd)
			update_pylst(self->tt->tags, self->i + 1, "STMT", 0, _ptr);
		else
			return (true);
	}
	return (get_assgt(self, self->i - 1, 0, false));
}
