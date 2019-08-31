#include "libft.h"

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
	return (ft_freejoin(key, token));
}

int		quoted_gold_key(char *gold_key)
{
	char	last_char;

	last_char = gold_key[ft_strlen(gold_key) - 1];
	return (in(gold_key[0], "\"", "'", NULL) && \
			in(gold_key[len_key - 1], "\"", "'", NULL));
}

// Check if the key have to be allocated or if
//we can just perform change on the string.
void	modify_gold_key(char *gold_key)
{
	if (quoted_gold_key(gold_key))
	{
		gold_key[len_key - 1] = '\0';
		ft_strcpy(gold_key, gold_key + 1);
	}
}
