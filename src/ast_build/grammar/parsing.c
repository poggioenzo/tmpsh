#include "libft.h"
#include "tmpsh.h"

/*
** is_value_line:
**
** @line: Line to check if it contain a keyword value,
**		  start with a tabulation or 4 spaces.
**
** return : - 1 if the line contain a value.
**			- 0 if the line do not contain a value.
*/

static int			is_value_line(const char *line)
{
	if (line && ft_strlen(line) > 0)
	{
		if (ft_incharset(line[0], "\t") || ft_start_with(line, "    "))
			return (1);
	}
	return (0);
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

static char			*get_keyword(const char *line)
{
	char	**split_key;
	char	*keyword;

	split_key = ft_strsplit(line, ":");
	keyword = ft_strtrim(split_key[0]);
	free_str_array(&split_key, 0);
	return (keyword);
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

static void			parse_keyword_values(char **lines, int *i)
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
		keyword_list = (t_pylst **)search_value_addr(g_grammar->grammar, \
				keyword);
	}
	ft_strdel(&keyword);
	while (is_value_line(lines[*i]))
	{
		value = ft_strtrim(lines[*i]);
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

void				get_grammar_from_path(void)
{
	char	*content;
	char	**lines;
	int		nbr_lines;
	int		i;

	content = readfile(g_grammar->path);
	lines = ft_strsplit(content, "\n");
	ft_strdel(&content);
	nbr_lines = ft_arraylen(lines);
	i = 0;
	while (i < nbr_lines)
	{
		if (ft_strlen(lines[i]) > 0 && !ft_incharset(lines[i][0], "\t\n#"))
			parse_keyword_values(lines, &i);
		else
			i++;
	}
	free_str_array(&lines, 0);
}
