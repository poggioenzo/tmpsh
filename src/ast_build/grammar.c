#include "libft.h"
#include "tmpsh.h"

t_grammar	*g_grammar = NULL;

void	show_tab(t_ht_table *table)
{
	char *key;
	t_ht_alveol *alveol;
	int index = 0;

	while (index < table->size)
	{
		ft_printf("%d:", index);
		alveol = table->items[index];
		while (alveol)
		{
			ft_printf("'%s':'%s', ", alveol->key, alveol->value);
			alveol = alveol->next;
		}
		ft_printf("\n");
		index++;
	}

}

/*
** get_keyword:
**
** @line: Line where a keyword have to be extract.
**
** In a given line, split the line to get only the keyword value, stripped.
**
** return : - Allocated keyword string.
*/

char		*get_keyword(char *line)
{
	char	**split_key;
	char	*keyword;

	if (!(split_key = ft_strsplit(line, ":")))
		exit(-1);
	if (!(keyword = ft_strtrim(split_key[0])))
		exit(-1);
	free_str_array(&split_key, 0);
	return (keyword);
}

/*
** is_value_line:
**
** @line: Line to check if it contain a keyword value,
**		  start with a tabulation or 4 spaces.
**
** return : - 1 if the line contain a value.
**			- 0 if the line do not contain a value.
*/

static int		is_value_line(char *line)
{
	if (line && ft_strlen(line) > 0)
	{
		if (ft_incharset(line[0], "\t") || ft_start_with(line, "    "))
			return (1);
	}
	return (0);
}

/*
** parse_keyword_values:
**
** @lines: All grammar file lines.
** @i: current index in the lines array.
**
** Whenever a keyword is found, store in a list each available
** value.
*/

static void		parse_keyword_values(char **lines, int *i)
{
	char	*keyword;
	char	*value;
	t_pylst	**keyword_list;

	keyword = get_keyword(lines[*i]);
	*i += 1;
	keyword_list = (t_pylst **)search_value_addr(g_grammar->grammar, keyword);
	if (!keyword_list)
	{
		insert_value(g_grammar->grammar, keyword, NULL, _pylst);
		keyword_list = (t_pylst **)search_value_addr(g_grammar->grammar, keyword);
	}
	while (is_value_line(lines[*i]))
	{
		if (!(value = ft_strtrim(lines[*i])))
			exit(-1);
		push_pylst(keyword_list, value, NO_COPY_BUT_FREE, _chare);
		*i += 1;
	}
}

/*
** get_grammar_from_path:
**
** Read the grammar text file, parse his content and store it
** into the g_grammar->grammar hash table.
**
** Formated like :
**		{
**			"keyword1" : ["val1", "val2", ...],
**			"keyword2" : [...],
**			...
**		}
*/

void get_grammar_from_path(void)
{
	char	*content;
	char	**lines;
	int		nbr_lines;
	int		i;

	if (!(content = readfile(g_grammar->path)))
		exit(-1);
	if(!(lines = ft_strsplit(content, "\n")))
		exit(-1);
	nbr_lines = ft_arraylen(lines);
	i = 0;
	while (i < nbr_lines)
	{
		if (ft_strlen(lines[i]) > 0 && !ft_incharset(lines[i][0], "\t\n#"))
			parse_keyword_values(lines, &i);
		else
			i++;
	}
}

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

static void	get_reverse_grammar(void)
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
static void		get_escape(void)
{
	t_pylst		*escape_lst;

	if ((escape_lst = search_value(g_grammar->grammar, "ESCAPE")))
		g_grammar->escape = escape_lst->value;
}

/*
** add_symbol:
**
** @symbol: representation of a new symbol.
** @symbol_name: name of the new symbol.
**
** Add a new pair of key/element into our g_grammar->grammar
** and or our reverse->background.
*/

static void		add_symbol(char *symbol, char *symbol_name)
{
	t_pylst		**tmp_lst;

	if (!search_value(g_grammar->grammar, symbol_name))
	{
		insert_value(g_grammar->grammar, symbol_name, NULL, _pylst);
		tmp_lst = (t_pylst **)search_value_addr(g_grammar->grammar, symbol_name);
		push_pylst(tmp_lst, symbol, 0, _chare);
	}
	insert_value(g_grammar->reverse, symbol, symbol_name, _chare);
}

int		containalphanum(char *str)
{
	while (*str)
	{
		if (ft_isalnum(*str++))
			return (1);
	}
	return (0);
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

/*
** get_maxlen:
**
** @iterator: list selected to search the max.
**
** Retrieve the max string's length inside a pyslt.
**
** return : Return max length.
*/

int		get_maxlen(t_pylst *iterator)
{
	int		max_len;
	int		new_len;
	char	*value;

	max_len = 0;
	while (pylst_iter(iterator, (void **)&value))
	{
		new_len = ft_strlen(value);
		if (new_len > max_len)
			max_len = new_len;
	}
	return (max_len);
}

void		store_tags(t_pylst *opening_tags)
{
	char	*tag;
	char	**tag_split;
	char	*tag_op;
	char	*tag_end;

	while (pylst_iter(opening_tags, (void **)&tag))
	{
		tag_split = ft_strsplit(tag, " ");
		tag_op = ft_strdup(tag_split[0]);
		tag_end = ft_strdup(tag_split[ft_arraylen(tag_split) - 1]);
		if (!tag_op || !tag_end)
			exit(-1);
		insert_value(g_grammar->opening_tags, tag_op, tag_end, _chare);
		free_str_array(&tag_split, 0);
	}
}

/*
** get_dquotes_opening_tags:
**
** Store in g_grammar->dquotes_opening_tags each available statement which
** are an opening element inside double quotes, like BRACEPARAM, DQUOTES etc.
*/

static void	get_dquotes_opening_tags(void)
{
	void	*tmp_search;

	if ((tmp_search = search_value(g_grammar->opening_tags, "BRACEPARAM")))
		insert_value(g_grammar->dquotes_opening_tags, "BRACEPARAM", \
				tmp_search, _ptr);
	if ((tmp_search = search_value(g_grammar->opening_tags, "CMDSUBST1")))
		insert_value(g_grammar->dquotes_opening_tags, "CMDSUBST1", tmp_search, _ptr);

}

/*
** get_abstract_terminator:
*/

static void	get_abstract_terminator(void)
{
	void	*tmp_search;
	t_pylst	*abs_term_lst;

	abs_term_lst = NULL;
	if ((tmp_search = search_value(g_grammar->grammar, "TERMINATOR")))
	{
		push_pylst(&abs_term_lst, "BACKGROUND_JOBS", 0, _chare);
		push_pylst(&abs_term_lst, "CMDAND", 0, _chare);
		push_pylst(&abs_term_lst, "CMDOR", 0, _chare);
		push_pylst(&abs_term_lst, "PIPE", 0, _chare);
		pylst_extend(&abs_term_lst, (t_pylst *)tmp_search, false);
		insert_value(g_grammar->grammar, "ABS_TERMINATOR", abs_term_lst, _pylst);
	}
}

static void	get_opening_tags(void)
{
	t_pylst		*opening_tags;
	t_pylst		*tmp_search;

	if ((tmp_search = search_value(g_grammar->grammar, "SUB_PROCESS")))
	{
		opening_tags = pylst_shacpy(tmp_search);
		if ((tmp_search = search_value(g_grammar->grammar, "QUOTES")))
			pylst_extend(&opening_tags, tmp_search, false);
		if ((tmp_search = search_value(g_grammar->grammar, "COMMAND_SH")))
			pylst_extend(&opening_tags, tmp_search, false);
		store_tags(opening_tags);
		if (search_value(g_grammar->grammar, "QUOTES"))
			get_dquotes_opening_tags();
	}
}

void	print_spaces(void);

void	shell_grammar_init(void)
{
	void	*tmp;

	push_pylst(&g_grammar->spaces, " ", 0, _chare);
	push_pylst(&g_grammar->spaces, "\t", 0, _chare);
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

void		print_lst(t_pylst *lst, void (*printer)(void *))
{
	void	*value;

	while (pylst_iter(lst, &value))
		printer(value);
}

void		print_lst2(t_pylst *lst)
{
	void	*value;

	while (pylst_iter(lst, &value))
		ft_printf("%s\n", (char *)value);;
}

int		printable_str(char *str)
{
	while (*str)
		if (!ft_isprint(*str++))
			return (0);
	return (1);
}

void	print_str(void *str)
{
	if (printable_str(str))
		ft_printf("%s\n", (char *)str);
	else
		ft_printf("%c\n", ((char *) str)[0]);
}
void	print_reverse_grammar(void)
{
	char	*key;
	char	*value;

	ft_printf("g_grammar->reverse:\n");
	ft_printf("{\n");
	while (ht_iter(g_grammar->reverse, &key, (void **)&value))
		ft_printf("    '%s':'%s'\n", key, value);
	ft_printf("}\n");
}

void	print_grammar(void)
{
	t_pylst		*value_lst;
	char		*key;
	char		*value;

	ft_printf("g_grammar->grammar:\n");
	ft_printf("{\n");
	while (ht_iter(g_grammar->grammar, &key, (void **)&value_lst))
	{
		ft_printf("    \"%s\" : [", key);
		while (pylst_iter(value_lst, (void **)&value))
			ft_printf("'%s', ", value);
		ft_printf("],\n");
	}
	ft_printf("}\n");
}

void	ft_puthidestr(char *str)
{
	while (*str)
	{
		if (*str == '\t')
			ft_putstr("\\t");
		else if (*str == '\n')
			ft_putstr("\\n");
		else if (*str == '\r')
			ft_putstr("\\r");
		else if (*str == '\v')
			ft_putstr("\\v");
		else if (*str == '\f')
			ft_putstr("\\f");
		else
			ft_putchar(*str);
		str++;
	}
}

void	print_spaces(void)
{
	char	*value;

	ft_printf("spaces:\n");
	ft_printf("[");
	while (pylst_iter(g_grammar->spaces, (void **)&value))
	{
		ft_printf("'");
		ft_puthidestr(value);
		ft_printf("', ");
	}
	ft_printf("]\n");
}

void	print_dquotes_opening_tags(void)
{
	char	*value;
	char	*key;

	ft_printf("dquotes_opening_tags:\n");
	ft_printf("{");
	while (ht_iter(g_grammar->dquotes_opening_tags, &key, &value))
		ft_printf("\"%s\" : \"%s\", ", key, value);
	ft_printf("}\n");
}

void	print_opening_tags(void)
{
	char	*value;
	char	*key;

	ft_printf("opening_tags:\n");
	ft_printf("{\n");
	while (ht_iter(g_grammar->opening_tags, &key, &value))
		ft_printf("    \"%s\" : \"%s\",\n", key, value);
	ft_printf("}\n");
}

void	print_escape(void)
{
	ft_printf("escape:\n");
	ft_printf("%s\n", g_grammar->escape);
}

void	print_leaf_op(void)
{
	char *operator;

	ft_printf("leaf_op:\n");
	ft_printf("[");
	while (pylst_iter(g_grammar->leaf_op, &operator))
	{
		ft_printf("'");
		ft_puthidestr(operator);
		ft_printf("',\n");
	}
	ft_printf("]\n");
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
	show_grammar_global();
	//print_grammar();
	//print_lst2(g_grammar->leaf_op); 
	//print_reverse_grammar();
}
