#include "libft.h"
#include "tmpsh.h"
#include "grammar_utils.h"

/*
** get_reverse_grammar:
**
** Parse the g_grammar->grammar hash table, and create a new dictionnary,
** with pylst values as keys, and g_grammar->grammar table's keys as values.
**
** Formated like :
** {
**		"value1" : "old_key1",
**		"value2" : "old_key2",
**		...
** }
*/

void	get_reverse_grammar(void)
{
	t_pylst	*lst_values;
	char	*key;
	char	*value;

	while (ht_iter(g_grammar->grammar, &key, (void **)&lst_values))
		while (pylst_iter(lst_values, (void **)&value))
			insert_value(g_grammar->reverse, value, key, _chare);
}

/*
** get_escape:
**
** Store the g_grammar->escape attribute using the available grammar.
*/

void		get_escape(void)
{
	t_pylst		*escape_lst;

	if ((escape_lst = search_value(g_grammar->grammar, "ESCAPE")))
		g_grammar->escape = escape_lst->value;
}

/*
** get_leaf_op:
**
** Get each shell operand of the grammar, store them
** in g_grammar->leaf_op.
*/

void		get_leaf_op(void)
{
	t_pylst		*list_op;
	char		*key;
	char		*value;

	list_op = NULL;
	while (ht_iter(g_grammar->reverse, &key, (void **)&value))
	{
		if (!containalphanum(key))
			push_pylst(&list_op, key, 0, _chare);
	}
	g_grammar->leaf_op = list_op;
}
