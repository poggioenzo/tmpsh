#include "heredocs.h"


/*
** str_heredocs:
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

static char	*quick_join(char *s1, char *s2, t_bool free_s1, t_bool free_s2)
{
	return (ft_fstrjoin(&s1, &s2, free_s1, free_s2));
}

char	*str_heredocs(t_heredocs *self)
{
	char	*str;
	char	*bool_str;

	str = quick_join("\nHEREDOC", self->key, false, false);
	str = quick_join(str, " | closed: ", true, false);
	bool_str = self->closed ? "True" : "False";
	str = quick_join(str, bool_str, true, false);
	str = quick_join(str, " | Minus: ", true, false);
	bool_str = self->minus ? "True" : "False";
	str = quick_join(str, bool_str, true, false);
	str = quick_join(str, "\n", true, false);
	str = quick_join(str, "DOC:\n", true, false);
	str = quick_join(str, str_tagstokens(self->tagstokens), true, true);
	return (str);
}
