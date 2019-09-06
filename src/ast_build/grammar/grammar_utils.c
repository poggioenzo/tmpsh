/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   grammar_utils.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: epoggio <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/03 21:47:37 by epoggio      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/03 21:47:40 by epoggio     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"
#include "tmpsh.h"

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
	while (iter_pylst(iterator, (void **)&value))
	{
		new_len = ft_strlen(value);
		if (new_len > max_len)
			max_len = new_len;
	}
	return (max_len);
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

void	add_symbol(char *symbol, char *symbol_name)
{
	t_pylst		**tmp_lst;

	if (!search_value(g_grammar->grammar, symbol_name))
	{
		insert_value(g_grammar->grammar, symbol_name, NULL, _pylst);
		tmp_lst = (t_pylst **)search_value_addr(g_grammar->grammar, \
				symbol_name);
		push_pylst(tmp_lst, symbol, 0, _chare);
	}
	insert_value(g_grammar->reverse, symbol, symbol_name, _static);
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
