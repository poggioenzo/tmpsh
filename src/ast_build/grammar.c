#include "libft.h"
#include "tmpsh.h"

t_grammar	*g_grammar = NULL;

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

static int		is_value_line(char **lines, int index)
{
	char	*analyse_str;

	analyse_str = lines[index];
	if (analyse_str && ft_strlen(analyse_str) > 0)
	{
		if (ft_incharset(analyse_str[0], "\t") || ft_start_with(analyse_str, "    "))
			return (1);
	}
	return (0);
}

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
	while (is_value_line(lines, *i))
	{
		if (!(value = ft_strtrim(lines[*i])))
			exit(-1);
		push_pylst(keyword_list, value, NO_COPY_BUT_FREE, _chare);
		*i += 1;
	}
}

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
		{
			parse_keyword_values(lines, &i);
		}
		else
			i++;
	}
}

void	grammar_init(char *path)
{
	if (!(g_grammar = MALLOC(sizeof(t_grammar))))
		exit(-1);
	g_grammar->path = path;
	ht_new_table(&g_grammar->grammar, 63, 40);
	ht_new_table(&g_grammar->reverse, 63, 40);
	get_grammar_from_path();
	//get_reverse_grammar();

}
