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

static t_bool check_aliases_token(t_tags_tokens_monitor *self)
{
	t_bool ret;

	ret = self->token ? true : false;
	ret &= ret && search_value(g_alias, self->token);
	ret &= ret && !in_pylst_chare(self->token, g_passed_alias);
	if (ret)
		push_pylst(&g_passed_alias, self->token, 0, _ptr);
	return (ret);
}

static t_bool cond_aliasing(t_tags_tokens_monitor *self, t_bool assignation)
{
	t_bool ret;
	t_bool is_alias;
	t_bool is_alias_token;

	ret = !(assignation);
	is_alias_token = check_aliases_token(self);
	is_alias = self->begin_cmd && is_alias_token;
	is_alias |= self->i == g_aliasindepth && is_alias_token;
	ret &= is_alias;
	return (ret);
}

t_bool		check_aliases_ttm(t_tags_tokens_monitor *self)
{
	t_bool	assignation;

	assignation = get_assgt(self, (int)self->tt->length, self->i + 1, true);
	if (cond_aliasing(self, assignation))
	{
		if (!in_pylst_chare(self->token, g_actual_alias))
		{
			self->begin_cmd = replace_alias_tagstokens(
				self->tt, self->token, self->i);
			strremove_pylst(&g_actual_alias, self->token);
		}
		else
			self->begin_cmd = replace_alias_tagstokens(
				self->tt, self->token, self->i);
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
