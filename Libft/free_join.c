
#include "libft.h"

char				*free_join(char *to_free, char *static_char, int delete)
{
	char *str;

	str = ft_strjoin(to_free, static_char);
	ft_strdel(&to_free);
	if (delete)
		ft_strdel(&static_char);
	return (str);
}
