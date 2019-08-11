#include "libft.h"
#include "tmpsh.h"

t_grammar	*g_grammar = NULL;

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

void	print_grammar(void)
{
	t_pylst	*values;
	char	*key;
	char	*value_str;

	while (ht_iter(g_grammar->grammar, &key, (void **)&values))
	{
		ft_printf("%s:\n", key);
		while (pylst_iter(values, (void **)&value_str))
			ft_printf("    %s\n", value_str);
	}
}

void	print_reverse_grammar(void)
{
	char	*key;
	char	*value;

	ft_printf("{\n");
	while (ht_iter(g_grammar->reverse, &key, (void **)&value))
		ft_printf("    '%s':'%s'\n", key, value);
	ft_printf("}\n");
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
	ft_printf("%s\n", getcwd(NULL, 0));
	if (!(g_grammar = MALLOC(sizeof(t_grammar))))
		exit(-1);
	g_grammar->path = path;
	ht_new_table(&g_grammar->grammar, 63, 40);
	ht_new_table(&g_grammar->reverse, 63, 40);
	get_grammar_from_path();
	print_grammar();
	get_reverse_grammar();
	print_reverse_grammar();
}
