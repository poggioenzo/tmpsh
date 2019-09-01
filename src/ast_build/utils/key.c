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

int		quoted_gold_key(char *gold_key)
{
	int len_key;

	len_key = ft_strlen(gold_key);
	return ((gold_key[0] == '\"' || gold_key[0] == '\'')
			&& (gold_key[len_key - 1] == '\"'
			|| gold_key[len_key - 1] == '\''));
}

void	modify_gold_key(char *gold_key)
{
	int len_key;

	len_key = ft_strlen(gold_key);
	if (quoted_gold_key(gold_key))
	{
		gold_key[len_key - 1] = '\0';
		ft_strcpy(gold_key, gold_key + 1);
	}
}
