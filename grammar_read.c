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

void		get_keyword(char **keyword, char *line)
{
	char	**splitted_line;

	if (!(splitted_line = ft_strsplit(line, ":")))
		exit(-1);
	if (!(*keyword = ft_strstrim(splitted_line[0])));
		exit(-1);
}


/*
** get_file_content:
**
** Get the entire content of the path given who contain the shell grammar.
** Split the current content.
*/

void	get_file_content(char ***lines, char *path)
{
	char	*text;

	if (!(text = ft_readfile(path)))
		exit(-1);
	if (!(*lines = ft_strsplit(text, "\n")))
		exit(-1);
	ft_strdel(&text);
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
			exit(-1);
		push_pylst(&keyword_syntax, syntax_elem, NO_COPY_BUT_FREE, \
				_chare);
		*index += 1;
	}
	if (!(insert_value(grammar, keyword, keyword_syntax, _pylst)))
		exit(-1);
}

int			get_grammar_from_path(char *path, t_ht_table **grammar)
{
	char	**lines;
	int		length;
	int		i;
	char	*keyword;

	get_file_content(&lines, path);
	len = ft_arraylen(lines);
	i = 0;
	grammar = NULL;
	if (!ht_new_table(grammar, 61, 30))
		exit(-1);
	while (i < length)
	{
		if (ft_strlen(lines[i] > 0 && !ft_incharset(lines[i][0], "#\t")))
		{
			get_keyword(&keyword, lines[i]);
			fill_keyword_grammar(*grammar, keyword, lines, &i);
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
