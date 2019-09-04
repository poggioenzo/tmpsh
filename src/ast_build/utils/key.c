/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   key.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: epoggio <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/03 22:11:01 by epoggio      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/04 19:20:01 by epoggio     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "utils.h"

char	*get_key(char *key, char *tag, char *token, t_bool minus)
{
	if (minus)
	{
		if (ft_strequ(key, "") && ft_strequ(tag, "SPACES"))
		{
			ft_strdel(&key);
			return (ft_strdup(""));
		}
	}
	return (free_join(key, token, false));
}

static int		squoted_gold_key(char *gold_key)
{
	int len_key;

	len_key = ft_strlen(gold_key);
	return (gold_key[0] == '\'' && gold_key[len_key - 1] == '\'');
}

int		dquoted_gold_key(char *gold_key)
{
	int len_key;

	len_key = ft_strlen(gold_key);
	return (gold_key[0] == '\"' && gold_key[len_key - 1] == '\"');
}

int				quoted_gold_key(char *gold_key)
{
	return (squoted_gold_key(gold_key) || dquoted_gold_key(gold_key));
}

void			modify_gold_key(char *gold_key)
{
	int len_key;

	len_key = ft_strlen(gold_key);
	if (quoted_gold_key(gold_key))
	{
		gold_key[len_key - 1] = '\0';
		ft_strcpy(gold_key, gold_key + 1);
	}
}
