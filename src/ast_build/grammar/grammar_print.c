#include "libft.h"
#include "tmpsh.h"
#include "grammar_print_attributes.h"

static void	print_grammar(void)
{
	t_pylst		*value_lst;
	char		*key;
	char		*value;

	ft_printf("g_grammar->grammar:\n");
	ft_printf("{\n");
	while (ht_iter(g_grammar->grammar, &key, (void **)&value_lst))
	{
		ft_printf("    \"%s\" : [", key);
		while (iter_pylst(value_lst, (void **)&value))
			ft_printf("'%s', ", value);
		ft_printf("],\n");
	}
	ft_printf("}\n");
}

static void	print_reverse_grammar(void)
{
	char	*key;
	char	*value;

	ft_printf("g_grammar->reverse:\n");
	ft_printf("{\n");
	while (ht_iter(g_grammar->reverse, &key, (void **)&value))
		ft_printf("    '%s':'%s'\n", key, value);
	ft_printf("}\n");
}

static void	print_escape(void)
{
	ft_printf("escape:\n");
	ft_printf("%s\n", g_grammar->escape);
}


void	show_grammar_global(void)
{
	print_grammar();
	print_reverse_grammar();
	print_spaces();
	print_escape();
	ft_printf("path:\n'%s'\n", g_grammar->path);
	ft_printf("g_grammar->maxlen_leaf_op:\n%d\n", g_grammar->maxlen_leaf_op);
	print_opening_tags();
	print_dquotes_opening_tags();
	print_leaf_op();
}
