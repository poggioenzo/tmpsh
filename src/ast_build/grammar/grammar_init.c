#include "tmpsh.h"
#include "libft.h"
#include "grammar_print.h"
#include "parsing.h"
#include "store_attributes.h"
#include "grammar_utils.h"

t_grammar	*g_grammar = NULL;

static void	shell_grammar_init(void)
{
	void	*tmp;

	g_grammar->spaces = " \t";
	ht_new_table(&g_grammar->opening_tags, 63, 40);
	ht_new_table(&g_grammar->dquotes_opening_tags, 63, 40);
	get_escape();
	add_symbol("\n", "NEW_LINE");
	get_leaf_op();
	if ((tmp = search_value(g_grammar->grammar, "ESCAPE")))
		pylst_strremove(&g_grammar->leaf_op, ((t_pylst *)tmp)->value);
	g_grammar->maxlen_leaf_op = get_maxlen(g_grammar->leaf_op);
	get_opening_tags();
	get_abstract_terminator();
}

/*
** grammar_init:
**
** @path: absolute path of the text file containing the grammar.
**
** Initialisation of the g_grammar globale variable, equivalent
** to an __init__ function.
** Setup each attribute of the variable, differents dictionnaries, lists etc.
*/

void	grammar_init(char *path)
{
	if (!(g_grammar = (t_grammar *)ft_memalloc(sizeof(t_grammar))))
		exit(-1);
	g_grammar->path = path;
	ht_new_table(&g_grammar->grammar, 63, 40);
	ht_new_table(&g_grammar->reverse, 63, 40);
	get_grammar_from_path();
	get_reverse_grammar();
	shell_grammar_init();
	// show_grammar_global();
}
