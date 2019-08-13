#include "tmpsh.h"
#include "libft.h"

static void		store_tags(t_pylst *opening_tags)
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
		//Perform a check to see if the key is already available,
		//will leak otherwise.
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

void	get_opening_tags(void)
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

/*
** get_abstract_terminator:
*/

void	get_abstract_terminator(void)
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
