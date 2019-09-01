/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   in_hash_g_grammar.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: epoggio <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/31 16:31:25 by epoggio      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/31 16:32:31 by epoggio     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "utils.h"

t_bool	in_grammar(char *tag, char *key)
{
	return (in_pylst_chare(tag, search_value(g_grammar->grammar, key)));
}

t_bool	in_reverse(char *tag, char *key)
{
	return (in_pylst_chare(tag, search_value(g_grammar->reverse, key)));
}

t_bool	in_opening_tags(char *tag, char *key)
{
	return (in_pylst_chare(tag, search_value(g_grammar->opening_tags, key)));
}

t_bool	in_dquotes_opening_tags(char *tag, char *key)
{
	return (in_pylst_chare(tag, search_value(
					g_grammar->dquotes_opening_tags, key)));
}
