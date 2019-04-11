#include "libft.h"

#define MALLOC_ERROR	0
#define MALLOC_SUCCESS	1

/*
** error_grammar:
**
** Freeing utils to use when an allocation error occur.
*/

int				error_grammar(char ***file_lines, t_ht_table **grammar, int status)
{
	if (file_lines)
		free_str_array(file_lines, NO_STATUS);
	if (grammar)
		free_hash_table(grammar, NO_STATUS);
	return (status);
	
}

/*
** get_keyword:
**
** For each new grammar element, get
** the element before the dobule column.
**
** Example : 
** ESCAPE:
**		\
**
** -> Will extract only ESCAPE word.
*/

int		get_keyword(char **keyword, char *line)
{
	char	**splitted_line;

	if (!(splitted_line = ft_strsplit(line, ":")))
		return (MALLOC_ERROR);
	if (!(*keyword = ft_strstrim(splitted_line[0])));
		return (free_str_array(&splitted_line, MALLOC_ERROR));
	return (MALLOC_SUCCESS);
}


/*
** get_file_content:
**
** Get the entire content of the path given who contain the shell grammar.
** Split the current content.
*/

int		get_file_content(char ***lines, char *path)
{
	char	*text;

	if (!(text = ft_readfile(path)))
		return (MALLOC_ERROR);
	*lines = ft_strsplit(text, "\n");
	ft_strdel(&text);
	return (*lines ? MALLOC_SUCCESS : MALLOC_ERROR);
}


int		fill_keyword_grammar(t_ht_table *grammar, char *keyword, char **lines, \
		int *index)
{
	t_pylst		*keyword_syntax;
	char		*syntax_elem;
	int			status;

	keyword_syntax = NULL;
	while (ft_strlen(lines[*index]) && lines[*index][0] == '\t' )
	{
		if (!(syntax_elem = ft_strstrim(lines[*index])))
			return (free_pylst(&keyword_syntax, MALLOC_ERROR));
		status = push_pylst(&keyword_syntax, syntax_elem, NO_COPY_BUT_FREE, \
				_chare);
		if (status == MALLOC_ERROR)
		{
			ft_strdel(&syntax_elem);
			return (free_pylst(&keyword_syntax, MALLOC_ERROR));
		}
		*index += 1;
	}
	status = insert_value(grammar, keyword, keyword_syntax, _pylst);
	if (status == MALLOC_ERROR)
		return (free_pylst(&keyword_syntax, MALLOC_ERROR));
	return (MALLOC_SUCCESS);
}

int			get_grammar_from_path(char *path, t_ht_table **grammar)
{
	char	**lines;
	int		length;
	int		i;
	char	*keyword;

	if (!get_file_content(&lines, path))
		return (MALLOC_ERROR);
	len = ft_arraylen(lines);
	i = 0;
	grammar = NULL;
	if (!ht_new_table(grammar, 61, 30))
		return (error_grammar(&lines, grammar, MALLOC_ERROR));
	while (i < length)
	{
		if (ft_strlen(lines[i] > 0 && !ft_incharset(lines[i][0], "#\t")))
		{
			if (!get_keyword(&keyword, lines[i]))
				return (error_grammar(&lines, grammar, MALLOC_ERROR));
			if (!fill_keyword_grammar(*grammar, keyword, lines, &i))
				return (error_grammar(&lines, grammar, MALLOC_ERROR));
		}
		i++;
	}
}


void		show_grammar(t_ht_table *grammar)
{
	
}

int		main(int argc, char **argv)
{
	t_ht_table *grammar;

	grammar = NULL;
	get_grammar_from_path(argv[1], &grammar);
	show_grammar(grammar);
}
