/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   store_attributes_2.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: epoggio <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/03 21:48:06 by epoggio      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/03 21:48:08 by epoggio     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "tmpsh.h"
#include "libft.h"

static void		store_tags(t_pylst *opening_tags)
{
	char	*tag;
	char	**tag_split;
	char	*tag_op;
	char	*tag_end;

	while (iter_pylst(opening_tags, (void **)&tag))
	{
		tag_split = ft_strsplit(tag, " ");
		tag_op = tag_split[0];
		tag_end = ft_strdup(tag_split[ft_arraylen(tag_split) - 1]);
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

static void		get_dquotes_opening_tags(void)
{
	void	*tmp_search;

	if ((tmp_search = search_value(g_grammar->opening_tags, "BRACEPARAM")))
		insert_value(g_grammar->dquotes_opening_tags, "BRACEPARAM", \
				tmp_search, _ptr);
	if ((tmp_search = search_value(g_grammar->opening_tags, "CMDSUBST1")))
		insert_value(g_grammar->dquotes_opening_tags, "CMDSUBST1", tmp_search, \
				_ptr);
}

void			get_opening_tags(void)
{
	t_pylst		*opening_tags;
	t_pylst		*tmp_search;

	if ((tmp_search = search_value(g_grammar->grammar, "SUB_PROCESS")))
	{
		opening_tags = pylst_shacpy(tmp_search);
		if ((tmp_search = search_value(g_grammar->grammar, "QUOTES")))
			extend_pylst(&opening_tags, tmp_search, FALSE);
		if ((tmp_search = search_value(g_grammar->grammar, "COMMAND_SH")))
			extend_pylst(&opening_tags, tmp_search, FALSE);
		store_tags(opening_tags);
		free_pylst(&opening_tags, 0);
		if (search_value(g_grammar->grammar, "QUOTES"))
			get_dquotes_opening_tags();
	}
}

/*
** get_abstract_terminator:
*/

void			get_abstract_terminator(void)
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
		extend_pylst(&abs_term_lst, (t_pylst *)tmp_search, false);
		insert_value(g_grammar->grammar, "ABS_TERMINATOR", abs_term_lst, \
				_pylst);
	}
}
